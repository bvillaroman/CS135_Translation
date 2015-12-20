#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
class vItem{
    public: 
        // inputs two string arguements into word and pos
        void setInfo(string s1,string s2);
        // returns the word in the vItem
        string getWord();
        // returns the position in the vItem
        string getPos();

    
    //the data members
    private:
        string word;
        string pos;
};
class Sentence{
    
    public:
        // sets the "sent" member
        void setData(string s1);
        // breaks the string into individual words
        vector<string> breakString();
        // sets each string with a pos defined in the english vocab, then adds it into the              vItems vector
        void setVector();
        //clears the vector
        void clearArray();
        // retrieves the vItems vector
        vector<vItem> getVitems();
        // overides the == operator to compare a vItem's pos and a string that is a pos 
        friend bool operator ==(vItem v1,string pos);  
    
        // the functions below are what TRANSLATES a vItem's word property, by looking         // through their POS 
    
        // finds the verb word in vItems and returns the translated vItem,if its is: if its a question then add the adjective to the "word" member, if its declrative then add adjective to the word member. Return the vItem with the new word
        vItem transVerb();
        // finds the subject word,adds its adjectives before it to the vItem.word and returns the translated vItem;
        vItem transSub();
        // if there is a direct object,adds its adjective before it to the vItem.word andreturn it's translated vItem
        vItem transDir();
        // checks to see if there is a direct object
        bool checkA(int index);
        //checks if the word is in the sentence
        bool checkI();
        // assigns the current vector with vector in the parameter
        void assignVector(vector<vItem> v);
        // records and returns all the adjectives before a noun
        string transAdj(int index);


    private:
        string sent;
        vector<vItem> vItems;
};
class Corpus{
    public:
        // retrieves the text data member
        vector<Sentence> getText();
        // *** TASK 1 ****:
        // OVERLOADS THE INPUT OPERATOR TO INPUT THE SENTENCES IN TEXT TO THE IS STREAM
        friend istream& operator >>(istream& is,Corpus& corp);
        // *** TASK 1 ****
    
        // *** TASK 3 ***:
        // OVERLOADS THE OUTPUT OPERATOR TO STUFF THE TRANSLATED SENTENCES FROM
        // corp.text sentences INTO THE OS STREAM
        friend ostream& operator <<(ostream& os,Corpus corp);
        // ** TASK 3 **

        void addText(Sentence S);
        
    private:
        vector<Sentence> text;
};

//size of the vocab array
const int MAXSIZE = 11;
vItem ENGvocab[MAXSIZE];

// populates an array
void populateArray(vItem In,int &size);
Corpus populateEngPP(Corpus corp,vector<vItem> v);
vector<vItem> translate(Sentence sent);
int main(){
    int size=0;
    Corpus ENGmm,EngPP;
    Sentence test ;
    ifstream text;
    ofstream transF;
    text.open("Eng--sents.txt");
    transF.open("Eng++trans.txt");
    
    vItem man,woman,fish,strong,Short,red,caught,kissed,is,a,the;
    
    man.setInfo("man","noun");
    woman.setInfo("woman","noun");
    fish.setInfo("fish","noun");
    strong.setInfo("strong","adjective");
    Short.setInfo("short","adjective");
    red.setInfo("red","adjective");
    caught.setInfo("caught","verb");
    kissed.setInfo("kissed","verb");
    is.setInfo("is","verb");
    a.setInfo("a","article");
    the.setInfo("the","article");
    
    populateArray(man,size);
    populateArray(woman,size);
    populateArray(fish,size);
    populateArray(strong,size);
    populateArray(Short,size);
    populateArray(red,size);
    populateArray(caught,size);
    populateArray(kissed,size);
    populateArray(is,size);
    populateArray(a,size);
    populateArray(the,size);
    
    text >> ENGmm ;
    
    //STARTS THE POPPULATING THE ENG++ SENTENCES BY TRANSLATING THE FIRST SENTENCE OBJECT IN ENGmm.TEXT property 
    EngPP = populateEngPP(ENGmm,translate(ENGmm.getText()[0]));
    transF << EngPP; 
    
    text.close();
    transF.close();
    
    return 0;
}

//     ******VITEMS*******
//  inputs parameter s1 is stored in word and parameter s2 is stored in pos
void vItem::setInfo(string s1,string s2){
    word = s1;
    pos = s2;
    
}
// returns the Pos data member
string vItem::getPos(){
    return pos;
}
// returns the word data member
string vItem::getWord(){
    return word;  
}  

//      ******SENTENCE*********
void Sentence::setData(string s1){
    sent = s1;  
}    
//breaks private member,sent, and breaks every word in the sentence 
vector<string> Sentence::breakString(){
    string temp;
    vector<string> returnVec;
    int length = sent.length();
    
    //iterates through each character in the sent.
    for(int i = 0; i < length; i++){
        //  if the sentence isn't a space, record the letter into temp
        if(sent[i] != ' '){
            temp += sent[i];
            if(i == length-1){
                returnVec.push_back(temp);   
            }
        }
        // if there is a space
        else if(sent[i] == ' '){
            //if there are more than one consecutive spaces,then keep reading the sentence until you find a letter. 
            if(sent[i+1] == ' '){
                while (sent[i] == ' '){
                    i++;
                }
                i--;
            }
            // put the value of temp into the returnVector
            returnVec.push_back(temp);
            //then reset temp value so that we get a new word
            temp = "";
        }
        
    }
    //return the vector 
    return returnVec;
    
    
}
void Sentence::setVector(){
    vector<string> stringV = breakString();
     // if the elements in the breakString vector match with an ENGvocab word, push that vItem into vItems
    for(int j = 0; j < stringV.size();j++){
        for(int i = 0;i <= MAXSIZE;i++){
            if(stringV[j]==ENGvocab[i].getWord()){
                vItems.push_back(ENGvocab[i]);
            }
        }
    }
    
}
void Sentence::clearArray(){
    int i=0;
    
    while (i < vItems.size()){
        vItems.pop_back();
    }
    
}
vector<vItem> Sentence::getVitems(){
    return vItems;
}
bool operator ==(vItem v1,string pos){
    if(v1.getPos() == pos){
        return true;   
    }
    else{
        return false;   
    }
    
}
void Sentence::assignVector(vector<vItem> v){
    vItems = v;   
    
}
//  **translates a word**
vItem Sentence::transVerb(){
    vItem returnV;
    string returnS;
    int end = vItems.size()-1;
    for(int i = 0; i <= end; i++){
        //if the current vItem is a verb
        if(vItems[i] == "verb"){
            // if the vItem.word is "is"
            if(checkI()== true){
                // if its a question,return the translation : adjective is-ka
                if(i==0){
                    //filters out the articles
                    while(vItems[i+1].getPos() != "adjective"){
                        i++;
                    }
                    
                    returnS = vItems[i+1].getWord() + " is-ka" ;
                }
                // if its a declarative, return the translation: adjective is
                else{
                    returnS =  vItems[i+1].getWord() + " is" ;   
                }

            }
            //other wise, leave the verb as is
            else{
                returnS = vItems[i].getWord();
            }
        }
        
    }
    // set the info for the translated verb and return
    returnV.setInfo(returnS,"verb");
    return returnV;
}
vItem Sentence::transSub(){
    vItem returnV;
    string returnS,adjectives;
    int i = 0;
    //looks for the index thats a noun and assign that into j
    while(vItems[i].getPos() != "noun" && i < vItems.size()){
        i++;
    }
    
    // if the words behind noun are adjectives
    if(i !=0 && checkA(i-1) == true){
        // find those adjectives and add them
        returnS = transAdj(i-1) + vItems[i].getWord()+"-ga" ;
    }
    else{
        //if there are no adjectives, just include : subject-ga
        returnS = vItems[i].getWord()+"-ga" ;   
    }
    //set the info and return
    returnV.setInfo(returnS,"noun");
    // return the translated vItem
    return returnV;
}
vItem Sentence::transDir(){
    vItem returnV;
    string returnS;
    int i = vItems.size()-1,j;
        
    //record that index into j
    j = i;
    // move one index before j
    i--;
    // if the words behind noun are adjectives
    if( checkA(i) == true){
        // the return word is translated into : adjectives direct-ga
        returnS = transAdj(i) + vItems[j].getWord()+"-o";
    }
    else{
        //if there are no adjectives, just include : direct-ga
        returnS = " " + vItems[j].getWord()+"-o" ;   
    }
    //set the info and return
    returnV.setInfo(returnS,"noun");
    
    return returnV;}
string Sentence::transAdj(int index){
    int count,j =index;
    string adjectives;
    while(index > 0 && checkA(index) == true){
        count ++;
        index--;
    }
    index++;
    // if there are consecutive adjectives, record all of them in side adjectives,other wise, record the only adjective
    while(index <= j){ 
        adjectives += vItems[index].getWord() + " ";
        index++;
    }
    
    // the return word is translated into : adjectives subject-ga
    return adjectives; 
    
    }
bool Sentence::checkA(int index){
    if(vItems[index] == "adjective"){
        return true;
    }
    else{
        return false;
    }
    
    }
bool Sentence::checkI(){
    int count = 0;
    for(int i = 0;i < vItems.size(); i++){
        if(vItems[i].getWord() == "is"){
            count++ ; 
        }
    }
    if(count != 0 ){
        return true;   
    }
    else{
        return false;
    }
}

//      *********CORPUS*************

vector<Sentence> Corpus::getText(){
    return text;  
}

//TASK 1: OVERLOD THE INPUT STREAM OPERATOR
istream& operator >>(istream& is,Corpus& corp){
    string tempS;
    Sentence Temp;
    while (!is.eof()){
        //  1) read a line from the stream
        getline(is,tempS);
          //  2) intializes the temp object with the input string s1,breaks the string into vitems and then stores each vItem into the vector vItems of the sentence object Temp.
        Temp.setData(tempS);
        Temp.breakString();
        Temp.setVector();
        // 3) then takes the Sentence object Temp and it gets pushed back to the text and then empties the data to be reused again.
        corp.text.push_back(Temp);
        Temp.clearArray();
        }

    return is;
}

//TASK 3 : OVERLOAD THE OUTPUT STREAM OPERATOR TO OUTPUT THE CORP.TEXT SENTENCES INTO THE OS STREAM
ostream& operator <<(ostream& os,Corpus corp){
        // recads the whole text vector
        for(int i = 0; i < corp.text.size() ; i++){
            // reads every vItem in each element of text
            for (int j =0 ; j < corp.text[i].getVitems().size(); j++ ){
                //stuffs the Word of each element into the os file
                os << corp.text[i].getVitems()[j].getWord() << " ";
                
            }
            os << endl;
        }
        
        return os;
}
void Corpus::addText(Sentence S){
    text.push_back(S);
}

// TASK 0 FUNCTION POPULATION ARRAY
// takes in 3 parameters : a vItem, and array filled with vItems, and the size of that array
void populateArray(vItem In,int &size){
    size++;
    
    //initializes the first element of the list
    if(size == 1){
        ENGvocab[0].setInfo(In.getWord(),In.getPos());
    }
    
    
    else {
        //from the end of the list to the front
        for (int i = size-1; i >= 0;i--){
            //temporary vItem object
            vItem temp;
        
            // initializes temp's word and pros. with the current index's word and pos
            temp.setInfo(ENGvocab[i].getWord(),ENGvocab[i].getPos()); 
            
            // initializes current index's word and pos data members with the next index's word and pos
            ENGvocab[i].setInfo(ENGvocab[i+1].getWord(),ENGvocab[i+1].getPos());
            
            // initializes next index's word and pos data members with the current index's word and pos
            ENGvocab[i+1].setInfo(temp.getWord(),temp.getPos()); 
            
        }
        // puts the new word into the very beginning of the array;
        ENGvocab[0].setInfo(In.getWord(),In.getPos());
    }
    
        
    
}


// transaltes a sentence object into eng++
vector<vItem> translate(Sentence sent){
    vector<vItem> returnV;
    
    //if the sentence has the word is,order is : subject adjective is-ka or: adjectives subject is
    if(sent.checkI() == true){
        returnV.push_back(sent.transSub());
        returnV.push_back(sent.transVerb());
    }
    
    // if its a declarative,the order is: adjectives subject adjectives direct object verb  
    else{
        returnV.push_back(sent.transSub());
        returnV.push_back(sent.transDir());
        returnV.push_back(sent.transVerb());

    }
    return returnV;
    
}

//  ***** TASK 2 ********
// takes in a Corpus object and a vector of vItems, and creates a new sent object, adds that sentence to a new corpus's text property, then, while new corpus's text size is less than the input corpus's size , translate each sentence object in corp.getText(), and put it in returnC's text property, then return the newly made corpus.
Corpus populateEngPP(Corpus corp,vector<vItem> v){
    Corpus returnC;
    Sentence Temp;
    int i =1;
        Temp.assignVector(v);
        //adds the text to the returnC
        returnC.addText(Temp);
        //clears the vector vItems to repeat
        Temp.clearArray();
    while(i < corp.getText().size()-1){
        Temp.assignVector(translate(corp.getText()[i]));
        //adds the text to the returnC
        returnC.addText(Temp);
        //clears the vector vItems to repeat
        Temp.clearArray();
        i++;
    }
    
    
    return returnC;
}



