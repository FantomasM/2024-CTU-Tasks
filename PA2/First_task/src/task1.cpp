#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#endif /* __PROGTEST__ */

 const int MAX_UTF8_1Byte_symbols = 127;
 const int MAX_UTF8_2Byte_symbols = 2047;
 const int MAX_UTF8_3Byte_symbols = 65535;
 const int MAX_UTF8_4Byte_symbols = 1114111;
/*class Code{
    vector<char> input_utf;
    vector<bool>fibcode;
    const char *inFile;
    const char * outFile;
public:
   bool openFile(){
       ifstream file(inFile,std::ios::binary | std::ios::in);
       if(file.is_open()==false || file.fail() || file.peek() == std::ifstream::traits_type::eof() ){
           return false;
       }
   }
   bool read_sequence(ifstream&file){
      char sign;
       if(file.get(sign).eof()){
          return false;
       }
        input_utf.push_back(sign);

   }

   void print_sequence(ofstream & oss){

       for(size_t i=0;i<fibcode.size();i+=8) {

           uint8_t byte = 0;
           for(size_t b=i+7;b>=i&&b<fibcode.size();b--){
               byte |=(fibcode[b] << (7-(b-i)));

           }
           //uint8_t byte2 =byte <<7;
           oss.write(reinterpret_cast<char*>(&byte),1);
       }
   }
};
*/



void change_to_fib(int n,vector<bool> &fib_code1){
    int maxfib=30;   //value of fib number 30 is 832040 and max utf8 number has value 1114111, so there is no need to take a bigger fib number
    vector<bool>fib_code;
    int fibonacci[30] = {1, 1};
    for (int i = 2; i < 30; i++) {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }
    while(fibonacci[maxfib-1]>n){
        maxfib--;
    }

    for(int i=maxfib;i >1;i--){
        int fibnum= fibonacci[i-1];
        if(n>= fibnum){




                fib_code.insert(fib_code.cbegin(), 1);
                n -= fibnum;



        } else{
            fib_code.insert(fib_code.cbegin(),0);
        }

    }
    fib_code.push_back(1);
    for(size_t i=0;i<fib_code.size();i++){
        fib_code1.push_back(fib_code[i]);
    }

}

bool Print_fibcode(vector<bool> fibcode,ofstream&oss) {

    for (size_t i = 0; i < fibcode.size(); i += 8) {

        uint8_t byte = 0;
        for (size_t b = i + 7; b >= i && b < fibcode.size(); b--) {
            byte |= (fibcode[b] << (7 - (i + 7 - b)));
        }

        oss.write(reinterpret_cast<char *>(&byte), 1);
    }
    if (oss.fail()) {
        cerr << "failbit";
        oss.close();
        return false;
    }
    return true;
}
bool               utf8ToFibonacci                         ( const char      * inFile,
                                                             const char      * outFile )
{
    ifstream file(inFile,std::ios::binary | std::ios::in);
    if(file.is_open()==false || file.fail() || file.peek() == std::ifstream::traits_type::eof() ){
        return false;
    }



    vector<char> buffer;
    char c;

    ofstream oss(outFile,std::ios::binary | std::ios::ate);
    oss.clear();

    if(!oss || !oss.is_open() ){

       return false;
    }
    vector<bool>fibcode(0);
    while(file.get(c)
           ) {

       // cout<<"working" <<endl;
        buffer.push_back(c);
        unsigned char c1=c;
        if((c1 & 0x80)==0) {

             int res=0;
            res=buffer[0];
            res++;
           // cout <<res;
            change_to_fib(res,fibcode);
            if(fibcode.size()%8==0 && fibcode.empty()== false){


                if(!Print_fibcode(fibcode,oss)){
                    oss.close();
                    return false;
                }




                fibcode.clear();
            }


            buffer.clear();
            continue;
        }
        if((c1 & 0xe0)==0xc0) {
            if(file.get(c).eof()== true || ((c &0xc0) !=0x80) ){
                oss.close();

                return false;

            }
            buffer.push_back(c);



             int res=0;
            res=((buffer[0] & 0x1f) << 6) | (buffer[1] & 0x3f);
            res++;
            change_to_fib(res,fibcode);
            if(fibcode.size()%8==0 && fibcode.empty()== false){
                //fibcode=lsb_right(fibcode);
                if(!Print_fibcode(fibcode,oss)){
                    oss.close();
                    return false;
                }
                fibcode.clear();
            }


            buffer.clear();
            continue;
        }

        if((c1 & 0xf0)==0xe0){
            for(int i=0;i<2;i++) {
                if(file.get(c).eof()== true || ((c &0xc0) !=0x80)){
                    oss.close();
                   // cerr << "Nespravny vstup";
                    return false;

                };
                buffer.push_back(c);
            }


             int res=0;
            res=((buffer[0] & 0x0f) << 12) | ((buffer[1] & 0x3f) << 6) | (buffer[2] & 0x3f);
            res++;
            change_to_fib(res,fibcode);
            if(fibcode.size()%8==0 && fibcode.empty()== false){
                //fibcode=lsb_right(fibcode);

                if(!Print_fibcode(fibcode,oss)){
                    oss.close();
                    return false;
                }
               fibcode.clear();
            }


            buffer.clear();
            continue;
        }
        if((c1 & 0xf8)==0xf0) {
            for(int i=0;i<3;i++) {
                if(file.get(c).eof()== true || ((c &0xc0) !=0x80)){

                   // cerr << "Nespravny vstup";
                    return false;

                };
                buffer.push_back(c);
            }

             int res=0;
            res=((buffer[0] & 0x07) << 18) | ((buffer[1] & 0x3f) << 12) | ((buffer[2] & 0x3f) << 6) | (buffer[3] & 0x3f);
            res++;
            change_to_fib(res,fibcode);
            if(fibcode.size()%8==0 && fibcode.empty()== false){
                //fibcode=lsb_right(fibcode);
                if(!Print_fibcode(fibcode,oss)){
                    oss.close();
                    return false;
                }
                fibcode.clear();
            }


            buffer.clear();
            continue;
        }
        else {
            oss.close();
            return false;
        }

    }
    if(!file.eof() || !oss.flush().good() || oss.fail()){

        return false;
    }

    if(fibcode.empty()== false) {
        for (size_t i = 0; i < (fibcode.size() % 8); i++) {
            fibcode.push_back(0);
        }


       // fibcode=lsb_right(fibcode);
        if(!Print_fibcode(fibcode,oss)){
            oss.close();
            return false;
        }


    }

    oss.close();
    return true;
    }





vector<bool> change_to_binary(int n,vector<bool> fibcode1){
    vector<bool>fibcode;

    while(n > 0){
        (n %2 ==0) ? fibcode.push_back(0) : fibcode.push_back(1) ;
        n/=2;
    }
    if(fibcode.size()%8!=0){

        for(size_t i=0;i<fibcode.size()%8;i++){
            fibcode.push_back(0);
        }

    }
    if(fibcode.empty()){
        for(size_t i=0;i<8;i++){
            fibcode.push_back(0);
        }
    }
    //vector<bool>fibcode_right= lsb_right(fibcode);



    for(size_t i=0;i<fibcode.size();i++){
        fibcode1.push_back(fibcode[i]);
    }
   
    return fibcode1;
}
bool print_to_file(size_t &is,vector<bool>& fibcode,ofstream& oss){
    int result=0;
    int fibonacci[31] = {1, 1};
    for (int i = 2; i < 30; i++) {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }
    for(size_t b=0;b<=is;b++){
        if(fibcode[b]==1){
            result+= fibonacci[b+2-1];
        }
    }



    result--;
    //cout <<result <<endl;
    if(result <=MAX_UTF8_1Byte_symbols){
        //oss<<char(result);
        uint8_t res1=result;
        oss.write(reinterpret_cast<char *>(&res1), 1);
        //cout<<char(result)<<endl;

        fibcode.erase(fibcode.cbegin(),fibcode.cbegin()+is+2);

        return true;
    }
    else if(result <= MAX_UTF8_2Byte_symbols){
    uint8_t res1=(((result)>>6) | 0xC0);
    oss.write(reinterpret_cast<char *>(&res1), 1);
    //oss.write(char((((result)>>6) | 0xC0)),1);
    uint8_t res2=((result & 0x3f) | 0x80);
        oss.write(reinterpret_cast<char *>(&res2), 1);
    //oss<<char(((result & 0x3f) | 0x80));

        fibcode.erase(fibcode.cbegin(),fibcode.cbegin()+is+2);

        return true;

    }
    else if(result <=MAX_UTF8_3Byte_symbols){
        uint8_t res1=((result>>12) |0xe0);
        uint8_t res2=(((result>>6) & 0x3f) |0x80);
        uint8_t res3=((result & 0x3f) | 0x80);
        oss.write(reinterpret_cast<char *>(&res1), 1);
        oss.write(reinterpret_cast<char *>(&res2), 1);
        oss.write(reinterpret_cast<char *>(&res3), 1);
        //oss<<char((result>>12) |0xe0);
   // oss<<char(((result>>6) & 0x3f) |0x80);

   // oss<<char((result & 0x3f) | 0x80);

        fibcode.erase(fibcode.cbegin(),fibcode.cbegin()+is+2);

        return true;
    }
    else if(result <=MAX_UTF8_4Byte_symbols){
        uint8_t res1=((result>>18) |0xf0);
        uint8_t res2=(((result >>12) &0x3f)|0x80);
        uint8_t res3=(((result>>6) & 0x3f) |0x80);
        uint8_t res4=((result & 0x3f) | 0x80);
        oss.write(reinterpret_cast<char *>(&res1), 1);
        oss.write(reinterpret_cast<char *>(&res2), 1);
        oss.write(reinterpret_cast<char *>(&res3), 1);
        oss.write(reinterpret_cast<char *>(&res4), 1);
       // oss<<char((result>>18) |0xf0);

       // oss<<char(((result >>12) &0x3f)|0x80);

       // oss<<char(((result>>6) &0x3f) |0x80);

       // oss<<char((result & 0x3f) | 0x80);

        fibcode.erase(fibcode.cbegin(),fibcode.cbegin()+is+2);

        return true;
    }
    cout << "brrrrr"<<endl;
    return false;

}
bool               fibonacciToUtf8                         ( const char      * inFile,
                                                             const char      * outFile ) {
    ifstream file(inFile, std::ios::binary | std::ios::in);


    if (file.is_open() == false || file.peek() == std::ifstream::traits_type::eof()) {
        //cerr <<"File is not open" <<endl;
        return false;
    }
    //cout <<"start 2" <<endl;

    vector<bool> fibcode;
    vector<bool> right_fibcode;

    ofstream oss(outFile, std::ios::binary | std::ios::ate);

    oss.clear();
    if (!oss || !oss.is_open()) {
        // cerr <<"Problems with output file" <<endl;
        oss.close();
        return false;
    }
    std::vector<unsigned char> data_FIB(1);
    while (file.read(reinterpret_cast<char*>(&data_FIB[0]), sizeof(data_FIB[0]))) {

        int y = data_FIB[0];

        //cout << c <<endl;
        fibcode=change_to_binary(y, fibcode);
        for (size_t i = 0; i < fibcode.size(); i++) {

            if (i != fibcode.size() - 1 && fibcode[i] == true && fibcode[i + 1] == true) {
                if (i > 30) {
                    // cerr <<"Fibonacci sequence is too long" <<endl;
                    return false; //Because fibonacci number starting from F(31) are higher than every UTF 8 sign value
                } else {

                    if (print_to_file(i, fibcode, oss) == false) {
                        oss.close();
                        return false;
                    } else {
                        if (!oss.flush().good() || oss.eof()) {
                            //cerr <<"Problems with output file" <<endl;
                            oss.close();
                            return false;
                        }
                        i=-1;
                    }


                }
            }

        }

    }







    for(size_t i=0;i<fibcode.size();i++){
        if(fibcode[i]== true){
           //cerr <<"Wrong sequence" <<endl;
            oss.close();
            return false;
        }
    }
    //cout <<endl;


    //file.close();
    oss.close();
    return true;




}

#ifndef __PROGTEST__

bool               identicalFiles                          ( const char      * file1,
                                                             const char      * file2 )
{
    //return true;
    ifstream f1(file1,ios::binary);
    ifstream f2(file2,ios::binary);

    if(f1.tellg()!=f2.tellg() ){
        return false;

    }
    f1.seekg(0, ifstream ::end);
    if (f1.tellg() == 0) {
        cout <<"file is empty" <<endl;
        return false;
    }

    f1.seekg(0,ifstream::beg);
    f2.seekg(0,ifstream::beg);
    return equal(istreambuf_iterator<char>(f1.rdbuf()),
                 istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(f2.rdbuf()));
}

int main ( int argc, char * argv [] )
{
    //cout<<"start" << endl;

    assert ( utf8ToFibonacci ( "example/src_0.utf8", "output.fib" )
             && identicalFiles ( "output.fib", "example/dst_0.fib" ) );
    assert ( utf8ToFibonacci ( "example/src_1.utf8", "output.fib" )
             && identicalFiles ( "output.fib", "example/dst_1.fib" ) );
    assert ( utf8ToFibonacci ( "example/src_2.utf8", "output.fib" )
             && identicalFiles ( "output.fib", "example/dst_2.fib" ) );
    assert ( utf8ToFibonacci ( "example/src_3.utf8", "output.fib" )
             && identicalFiles ( "output.fib", "example/dst_3.fib" ) );
    assert ( utf8ToFibonacci ( "example/src_4.utf8", "output.fib" )
             && identicalFiles ( "output.fib", "example/dst_4.fib" ) );
    assert ( ! utf8ToFibonacci ( "example/src_5.utf8", "output.fib" ) );
    assert ( fibonacciToUtf8 ( "example/src_6.fib", "output.utf8" )
             && identicalFiles ( "output.utf8", "example/dst_6.utf8" ) );
    assert ( fibonacciToUtf8 ( "example/src_7.fib", "output.utf8" )
             && identicalFiles ( "output.utf8", "example/dst_7.utf8" ) );
    assert ( fibonacciToUtf8 ( "example/src_8.fib", "output.utf8" )
             && identicalFiles ( "output.utf8", "example/dst_8.utf8" ) );
    assert ( fibonacciToUtf8 ( "example/src_9.fib", "output.utf8" )
             && identicalFiles ( "output.utf8", "example/dst_9.utf8" ) );
    assert ( fibonacciToUtf8 ( "example/src_10.fib", "output.utf8" )
             && identicalFiles ( "output.utf8", "example/dst_10.utf8" ) );
    assert ( ! fibonacciToUtf8 ( "example/src_11.fib", "output.utf8" ) );
    assert ( ! utf8ToFibonacci( "in_5028599.bin", "output.utf8" ) );
    assert(!utf8ToFibonacci( "fd", "ouptut.utf8" ));
    assert(!fibonacciToUtf8 ( "fd", "ouptut.utf8" ));
    fibonacciToUtf8 ( "fa.fib", "ouptut.utf8" );
    utf8ToFibonacci ( "fa.fib", "ouptut.utf8" );
    assert (fibonacciToUtf8 ( "in_5030576.bin", "output.utf8" )  && identicalFiles ( "output.utf8", "ref_5030576(1).bin" ) );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
