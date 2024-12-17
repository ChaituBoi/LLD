#include <iostream>
#include <memory>
#include <cassert>
#include <string>
#include <vector>
#define MAX 5
class Document
{
    private:
    public:
        virtual void open()=0;
        virtual void close()=0;
        virtual std::string save() = 0;
        //clone
        virtual Document *clone() = 0;

        virtual ~Document() {}//important
};

class textDoc : public Document
{
    private:
        std::string fileName;//should be diff
        std::string filePath;
        std::string *data;///[MAX] size only

    public:
        //constructor
        textDoc(textDoc& src)//will come in handy during clone
        {
            this->fileName = src.fileName;
            this->filePath = src.filePath;
            this->data = new std::string[MAX];//deep copy to MAX size
            for(int ind=0;ind<MAX;ind++)
            {
                this->data[ind] = src.data[ind];
            }
        }
        textDoc(){}//empty constr
        textDoc(std::string fileName,std::string filePath,std::string* data)
        {
            this->fileName = fileName;
            this->filePath = filePath;
            this->data = new std::string[MAX];
            for(int ind=0;ind<MAX;ind++)//deep copy
            {
                this->data[ind] = data[ind];
            }
        }
        ~textDoc()//important
        {
            delete[] this->data;
        }

        void open()
        {
            std::cout << "Opening file " << fileName << " from path " << filePath << "."<<std::endl;
            for (int ind = 0;ind<MAX;ind++)
            {
                std::cout << data[ind] << std::endl;
            }
        }
        void close()
        {
            std::cout << "Closing file " << fileName <<"."<<std::endl;
        }
        std::string save()
        {
            std::cout << "Saving file " << fileName << " to path " << filePath << "."<<std::endl;
            return filePath;
        }
        //clone
        Document* clone()
        {
            return new textDoc(*this);
        }
};

int main()
{
    std::string data[] = {"This is Chaitanya.", "I am 24 years old.", "I love playing Badminton.", "I also love playing video games.", "My favourite food is Pizza."};
    std::string fileName = "Chaitanya.txt";
    std::string filePath = "C://Documents/MyFiles/";
    
    Document *doc1 = new textDoc(fileName,filePath , data); //
    // doc1->open();
    // doc1->save();
    // doc1->close();

    Document *doc2 = doc1->clone();//
    
    doc2->open();//same as doc1 o/p because they are clones now.
    doc2->save();
    doc2->close();


    delete doc1;
    delete doc2;
    return 0;
}
