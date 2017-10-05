#include <iostream>
using std::string;

struct Counter{
    int count;
    Counter(){
        count=0;
    }
};

int main(){
    // M length marker (initialized ????)
    int m;
    string s;
    // Read pattern of length equal or smaller than m
    std::cin>>m;
    std::cin>>s;
    string s1, s2;
    int textLength = s.size();
    if (textLength < 2*m)
        std::cout<<"ERROR: The text must be bigger than the pattern\n";

    Counter m_counter; //this counter will check the m length condition
    for(int i=0 ; i < textLength ; i++){
        s1.push_back(s[i]);
        m_counter.count += 1;
        if(m_counter.count == 2*m || i == textLength-1){
            s1.push_back('$');
            m_counter.count = 0;
        }
    }

    for(int i=m ; i < textLength ; i++){
        s2.push_back(s[i]);
        m_counter.count += 1;
        if(m_counter.count == 2*m || i == textLength-1){
            s2.push_back('$');
            m_counter.count = 0;
        }
    }

    string result = s1+"!"+s2;
    std::cout<<result+"\n";
}
