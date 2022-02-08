#include <iostream>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <list>

using namespace std;

class tweet {
public:    
    string username{""};
    int id {0};
    set<string> likes;
    tweet *rt {nullptr};
    string mensagem{""};
    bool is_delete {false};
public:
    tweet(string username, int id, string mensagem) : username{username}, id{id}, mensagem{mensagem} {}
    
    int get_id() { return id; }
    string get_username() { return username; }
    string get_mensagem() { return mensagem; }

    friend ostream& operator<<(ostream& os, const tweet& t) {
        if(t.is_delete) {
            os << "Deleted tweet" << endl;
        } else {
            os << "Tweet: " << t.mensagem << endl;
            os << "User: " << t.username << endl;
            os << "ID: " << t.id << endl;
            os << "Likes: ";
            for(auto& l : t.likes) {
                os << l << ", ";
            }
            os << endl;
            if(t.rt != nullptr) {
                os << "Retweeted: " << t.rt->mensagem << endl;
            }
        }
        return os;
    }

    void like(string username) {
        if(likes.find(username) == likes.end()) {
            likes.insert(username);
        } else {
            throw runtime_error("Usuario ja curtiu");
        }
    }
    set<string> get_likes() { return likes; }

    void retwit(tweet *t) {
       this->rt = t;
    }
    void delete_tweet() {
        is_delete = true;
    }
    bool is_deleted() {
        return is_delete;
    }
    
};
class Inbox{
private:
    map<int, tweet*> timeline;
    map<int, tweet*> mytweets;
public:
    Inbox() {}
    void storeInTimeLine(tweet* t) {
        timeline.insert(pair<int, tweet*>(t->get_id(), t));
    }
    list<tweet*> get_timeline() {
        list<tweet*> l;
        for(auto& t : timeline) {
            l.push_back(t.second);
        }
        return l;
    }
    void storeInMyTweets(tweet* t) {
        mytweets.insert(pair<int, tweet*>(t->get_id(), t));
    }

    friend ostream& operator<<(ostream& os, const Inbox& i) {
        os << "Timeline: " << endl;
        for(auto& t : i.timeline) {
            os << *t.second << endl;
        }
        os << "My tweets: " << endl;
        for(auto& t : i.mytweets) {
            os << *t.second << endl;
        }
        return os;
    }
    void rmMsgsFrom(string username) {
        for(auto& t : mytweets) {
            if(t.second->get_username() == username) {
                t.second->delete_tweet();
            }
        }
    }
    list<tweet*> get_mytweets() {
        list<tweet*> l;
        for(auto& t : mytweets) {
            l.push_back(t.second);
        }
        return l;
    }
    tweet* getTweet(int id) {
        auto it  = timeline.find(id);
        if (it == timeline.end()){
           throw runtime_error("Mensagem nao encontrada\n");
        }
        return it->second;
    }

};

class user{
private:    
    string username;
    Inbox inbox;
    map<string, user*> followers;
    map<string, user*> following;
public:
    user(string username) : username{username} {}
    string get_username() { return username; }

    void follow(user* usuario){
        if(following.find(usuario->get_username()) == following.end()) {
           usuario->followers[this->username] = this;
           this->following[usuario->get_username()] = usuario;
           
        } else {
            throw runtime_error("voce ja segue esse usuario");
        }
    }

    void send_tweet(tweet *tweet) {
        this->inbox.storeInTimeLine(tweet);
        this->inbox.storeInMyTweets(tweet);

        for (auto [key, user] : followers) {
            user->inbox.storeInTimeLine(tweet);
        }
    }
    Inbox& get_inbox() {
        return this->inbox;
    }

    void unfollow(user* usuario){
        auto key = usuario->username;
        if (following.find(key) != following.end()) {
            this->inbox.rmMsgsFrom(usuario->username);
            this->following.erase(key);
            usuario->followers.erase(this->username);
        }
    }
    void like(int tweet_id){
        auto t = this->inbox.getTweet(tweet_id);
        t->like(this->username);
    }

    void unfollowAll() {
        vector<user*> remSeguidos;
        for (auto user : this->following) {
            remSeguidos.push_back(user.second);
        }

        for (auto user : remSeguidos) {
            this->following.erase(user->username);
            user->followers.erase(this->username);
        }    
    }
    void rejectall() {
         vector<user*> remSeguidores;
        for (auto user : this->followers) {
            remSeguidores.push_back(user.second);
        }

        for (auto user : remSeguidores) {
            this->followers.erase(user->username);
            user->following.erase(this->username);
        }
    } 

    friend ostream& operator<<(ostream& os, const user& u) {
        os << "User: " << u.username << endl;
        os << "Following: " << endl;
        for(auto& u : u.following) {
            os << u.first << endl;
        }
        os << "Followers: " << endl;
        for(auto& u : u.followers) {
            os << u.first << endl;
        }
        return os;
    }

};

class controller{
private:
    int next_id = 0;
    map<string, shared_ptr<user>> users;
    map<string, shared_ptr<tweet>> tweets;

    tweet *create_tweet(string username, string mensagem) {
        auto t = make_shared<tweet>(username, next_id, mensagem);
        tweets[username] = t;
        next_id++;
        return t.get();
    }
public: 
    void add_user(string username) {
        if(users.find(username) == users.end()) {
            users[username] = make_shared<user>(username);
        } else {
            throw runtime_error("Usuario ja existe");
        }
    }
    
    user *getUser(const string &username){
        if (this->users.find(username)->first == username){
            return this->users.find(username)->second.get();
        }
        throw runtime_error("fail: usuario nao encontrado");
        
    }
    void send_tweet(string username, string mensagem) {
        auto t = create_tweet(username, mensagem);
        auto usuario = getUser(username);
        usuario->send_tweet(t);
    }
     void sendRt(string nome, int twId, string msg) {
        auto user = getUser(nome);
        auto tweetRt = user->get_inbox().getTweet(twId);
        auto novoTweet = this->create_tweet(nome, msg);
        novoTweet->retwit(tweetRt);
        user->send_tweet(novoTweet);
    }
     void remove(string nome) {
        auto user = getUser(nome);
        user->unfollowAll();
        user->rejectall();

        for (auto tweet : user->get_inbox().get_mytweets()) {
            tweet->delete_tweet();
        }

        this->users.erase(nome);
    }

    friend ostream& operator<<(ostream& os, const controller& c) {
        for(auto& u : c.users) {
            os << *u.second << endl;
        }
        return os;
    }
};
int main(){
    controller controle;

    
    
    cout << "Digite Comandos para obter a lista deles " << endl;

    while(true){
    
    cout << endl;
    string line{}, cmd{};
    getline(cin, line);
    stringstream ss(line);
    ss >> cmd;
    cout << "$" << line << endl;
    
    try{
        if(cmd == "adduser") {
            string username;
            ss >> username;
            controle.add_user(username);
        } else if (cmd == "comandos"){
            cout << "adduser <username>" << endl;
            cout << "send <username> <mensagem>" << endl;
            cout << "sendrt <username> <mensagem> <twId>" << endl;
            cout << "remove <username>" << endl;
            cout << "list" << endl;
            cout << "follow <username> <seguidor>" << endl;
            cout << "unfollow <username> <seguidor>" << endl;
            cout << "like <username> <twId>" << endl;
            cout << "unfollowall <username>" << endl;
            cout << "rejectall <username>" << endl;
            cout << "timeline <username>" << endl;
            cout << "sair" << endl;
        } else if (cmd == "send") {
            string username, mensagem;
            ss >> username >> mensagem;
            controle.send_tweet(username, mensagem);
        } else if (cmd == "sendrt") {
            string username, mensagem;
            int twId;
            ss >> username >> mensagem >> twId;
            controle.sendRt(username, twId, mensagem);
        } else if (cmd == "remove") {
            string username;
            ss >> username;
            controle.remove(username);
        } else if (cmd == "list") {
            cout << controle;
        } else if (cmd == "follow") {
            string username, seguidor;
            ss >> username >> seguidor;
            controle.getUser(username)->follow(controle.getUser(seguidor));
        } else if (cmd == "unfollow") {
            string username, seguidor;
            ss >> username >> seguidor;
            controle.getUser(username)->unfollow(controle.getUser(seguidor));
        } else if (cmd == "like") {
            string username;
            int twId;
            ss >> username >> twId;
            controle.getUser(username)->like(twId);
        } else if (cmd == "unfollowall") {
            string username;
            ss >> username;
            controle.getUser(username)->unfollowAll();
        } else if (cmd == "rejectall") {
            string username;
            ss >> username;
            controle.getUser(username)->rejectall();
        } else if (cmd == "sair") {
            break;
        } else if (cmd == "timeline") {
            string username;
            ss >> username;
            cout << controle.getUser(username)->get_inbox() << endl;
        } else {
            cout << "Comando invalido" << endl;
        }
        
    }
    catch(runtime_error& e){
        cout << e.what() << endl;
    }
    }
}
           