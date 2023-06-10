#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

char str[10001];//开全局数组为字符串的输入以及储存

int findloc(char *s){//查找用作运算符的‘-’和‘+’
    int len=strlen(s);
    int i;
    for(i=len-1;i>=0;i--){
        if((s[i]=='-'&&(s[i-1]==')'||(s[i-1]>='0'&&s[i-1]<='9')))||s[i]=='+') return i;//如果找到，返回加减运算符的位置
        else if(s[i]==')'){//做跳过括号的处理
            int cnt=0;
            int j,cnt_left=0;
            for(j=i;j>=0;j--){
                if(s[j]==')') cnt++;
                if(s[j]=='(') cnt_left++;
                if(cnt_left==cnt){//如果找到与从右数第一个‘）’对应的‘（’
                    i=j;//跳过最外层的括号进行运算符的检索
                    break;
                }
            }
        }
    }
    return -1;//找不到则返回-1
}

int findloca(char *s){//查找*，/，%运算符
    int len=strlen(s);
    int i;
    for(i=len-1;i>=0;i--){
        if(s[i]=='/'||s[i]=='*'||s[i]=='%') return i;//如果找到，返回运算符的位置
        else if(s[i]==')'){//跳过括号处理,与findloc的处理相同
            int cnt=0;
            int j,cnt_left=0;
            for(j=i;j>=0;j--){
                if(s[j]==')') cnt++;
                if(s[j]=='(') cnt_left++;
                if(cnt_left==cnt){
                    i=j;
                    break;
                }
            }
        }
    }
    return -1;//找不到则返回-1
}

int Isdigit(char *s){//判断一个字符串是否是数字
    int flag=1;
    int i;
    int len=strlen(s);
    for(i=0;i<len;i++){
        if(s[i]>'9'||s[i]<'0'){//超出0~9这个范围则返回0，代表有除数字之外的字符
            flag=0;
            break;
        }
    }
    return flag;
}

int f(char *s){//进行计算的函数
    if(Isdigit(s)){//如果是数字，则返回对应的整数值
        return atoi(s);//atoi实现字符串变整数
    }
    else if(s[0]=='-'&&findloc(s)==-1&&findloca(s)==-1) return -1*f(&s[1]);//如果是负数，返回对应的数值
    else {//表达式的计算
        if(s[0]=='('&&s[strlen(s)-1]==')') {//如果两端是括号，去除括号再进行计算
            s[strlen(s)-1]=0;
            return f(&s[1]);
        }else {
        int loc=findloc(s);//找到+，-运算符，分为前后两个部分计算
        if(loc>=0){
            char op=s[loc];
            s[loc]=0;
            switch(op){//判断是加还是减
                case '+':return f(s)+f(&s[loc+1]);break;
                case '-':return f(s)-f(&s[loc+1]);break;
                default:printf("Findloc Error:%c\n",op);return 12345;break;//错误提醒
            }
        }
        else if(loc==-1){
            int loca=findloca(s);//找到*，/，%运算符，分为前后两个部分计算
            char ops=s[loca];
            s[loca]=0;
            switch(ops){
                case '*':return f(s)*f(&s[loca+1]);break;
                case '/':return f(s)/f(&s[loca+1]);break;
                case '%':return f(s)%f(&s[loca+1]);break;
                default:printf("Findloca Error:%c\n",ops);return 12345;break;//错误提醒
            }
        }
        }
    }
    return 666666;//保证返回值（为了去掉编译器的“Warning”）
}

int main(){//运算的主函数
    scanf("%s",str);//输入字符串
    printf("%d",f(str));//输出结果
    return 0;
}
