namespace IO{ 
    #define BUF_SIZE 100000 
    #define OUT_SIZE 100000 

    bool IOerror=0; 
    inline char nc(){ 
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE; 
        if(p1==pend){ 
            p1=buf;pend=buf+fread(buf,1,BUF_SIZE,stdin); 
            if(pend==p1){IOerror=1;return -1;} 
        } 
        return *p1++; 
    } 
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';} 
    inline bool read(double &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for(;blank(ch);ch=nc()); 
        if(IOerror) return false; 
        if(ch=='-')sign=1,ch=nc(); 
        for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if(ch=='.'){ 
            double tmp=1;ch=nc(); 
            for(;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0'); 
        } 
        if(sign)x=-x;return true;
    }
    template<typename T>
    inline bool read(T &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for(;blank(ch);ch=nc()); 
        if(IOerror) return false; 
        if(ch=='-')sign=1,ch=nc(); 
        for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if(sign)x=-x; return true;
    } 
    inline bool read(char *s){ 
        char ch=nc(); 
        for(;blank(ch);ch=nc()); 
        if(IOerror) return false; 
        for(;!blank(ch)&&!IOerror;ch=nc())*s++=ch; 
        *s=0;return true;
    } 
};
using namespace IO;

freopen("/Users/wzw/Desktop/ACM/1.in","r",stdin);
