/*
Author: Anna Ponamarchuk
Course: CSCI-135
Instructor: Gennady Maryash
Assignment: Project 2 c

calculates the Hamming distance between two strings
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <climits>

using namespace std;

//comparing two strings
int find_difference(string a, string b){
   int diff = 0;
   for (int i=0; i<a.length(); i++){
      if(a[i] != b[i]){
         diff++;
      }
   }
   if(a.length() != b.length()){
      diff++;
   }
   return diff;
}

//reads from file with one in linr space 
//and returns acids string
string dictionary_read(ifstream &dict, string s, bool & met) {
    string key, value;
    // reset error state
    dict.clear(); 
    // return file pointer to the beginning 
    dict.seekg(0); 
    string code;
    
    while (dict >> key >> value) {
         if(key == s && value == "Stop"){
            met = false;
         }
         if(key == s && value == "Met"){
            met = true;
         }
         if(key == s&& met ==true){
            code = value;
         }
    }
    return code;
}

//passes encoded dna to the function that reads file
string compare(string s){
   ifstream fin("codons.tsv");
   if (fin.fail()) {
      cerr << "File cannot be read, opened, or does not exist.\n";
      exit(1);
   }

   string c;
   string acids_code;
   bool met = false;
   for(int i=0; i<s.length(); i=i+3){
      c = s.substr(i, 3);
      
      acids_code += dictionary_read(fin, c, met);
   }
   fin.close();//closing file

   return acids_code;
}

// switches dna
char switchLetter(char a){
   switch(a) {
      case 'A' :
         a = 'U'; 
         break;
      case 'T' :
         a = 'A'; 
         break;
      case 'C' :
         a = 'G';
         break;
      case 'G' :
         a = 'C';
         break;
   }
   return a;
}


//reads file with encoded dna
int transcript(){
   ifstream fin("mutations.txt");
   //error
   if (fin.fail()) {
      cerr << "File cannot be read, opened, or does not exist.\n";
      exit(1);
   }
   string strand;
   string s;
   bool if_odd = true;
   string odd, even, odd_acids, even_acids;
   //reads line
   while(getline(fin, strand)) {
      //sets odd lines to var
      if(if_odd == true){
         odd = strand;
         if_odd = false;
      }else{
         //sets even lines to var
         even = strand;
         if_odd = true;
         //outputs value
         if(find_difference(odd, even)==0){
            cout <<find_difference(odd, even)<<" no"<<endl;
         }else{
            cout <<find_difference(odd, even)<<" ";
            for (int i=0; i<strand.length(); i++){
        
               odd[i] = toupper(odd[i]);
               if(i ==0){
                  odd_acids = switchLetter(odd[i]);
                  even_acids = switchLetter(even[i]);
               }else{
                  odd_acids += switchLetter(odd[i]);
                  even_acids += switchLetter(even[i]);
               }
               

            }
            if(find_difference(compare(odd_acids),compare(even_acids)) == 0){
               cout<<"no"<<endl;
            }else{
               cout <<"yes"<<endl;
            }
            
         }
         
      }
      
      
   }
   //closes file
   fin.close();

   return 0;
}



int main()
{
   transcript();
   
   return 0;
}

