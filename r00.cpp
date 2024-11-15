#include<iostream>
#include<string>
#include<vector>

std::string printVector(std::vector<std::string> &v){
    std::string res{"{"};
    for (std::string el : v) {res+=el + ",";}
    res+="}";
    return res;
}

class Verb{
    public:
        std::vector<std::string> ind_present_singular;
        std::vector<std::string> ind_present_plural;
        std::vector<std::string> ind_psimple_singular;
        std::vector<std::string> ind_psimple_plural;
        std::vector<std::string> ind_futur_singular;
        std::vector<std::string> ind_futur_plural;
        std::vector<std::string> ind_conditi_singular;
        std::vector<std::string> ind_conditi_plural;
        std::string infinitive = "";

        Verb(std::string inf_d, std::vector<std::string> formList){            // Constructor
        infinitive = inf_d;
        int f{0};
        for (int i=f; i<f+3; i++) {ind_present_singular.push_back(formList[i]);}f=f+3;
        for (int i=f; i<f+3; i++) {ind_present_plural.push_back(formList[i]); }f=f+3;
        for (int i=f; i<f+3; i++) {ind_psimple_singular.push_back(formList[i]);}f=f+3;
        for (int i=f; i<f+3; i++) {ind_psimple_plural.push_back(formList[i]);}f=f+3;
        for (int i=f; i<f+3; i++) {ind_futur_singular.push_back(formList[i]);}f=f+3;
        for (int i=f; i<f+3; i++) {ind_futur_plural.push_back(formList[i]); }f=f+3;
        }
        
};



void printVerbTable(Verb verb){
    std::cout << "----- VERB TABLE: " << verb.infinitive << " -------" << std::endl;
    // Indicative present
    std::cout << "Indicative present, singular: ";
    std::string res{};
    for (std::string el : verb.ind_present_singular) {res+=el + " ";}
    std::cout << res << std::endl;res.clear();
    

    std::cout << "Indicative present, plural: ";
    for (std::string el : verb.ind_present_plural) {res+=el + " ";}
    std::cout << res << std::endl;res.clear();

    std::cout << "Passé simple, singular: ";
    for (std::string el : verb.ind_psimple_singular) {res+=el + " ";}
    std::cout << res << std::endl;res.clear();

    std::cout << "Passé simple, plural: ";
    for (std::string el : verb.ind_psimple_plural) {res+=el + " ";}
    std::cout << res << std::endl;res.clear();

    std::cout << "Futur, singular: ";
    for (std::string el : verb.ind_futur_singular) {res+=el + " ";}
    std::cout << res << std::endl;res.clear();

    std::cout << "Futur, plural: ";
    for (std::string el : verb.ind_futur_plural) {res+=el + " ";}
    std::cout << res << std::endl;res.clear();
    
    std::cout << "------------------" << std::endl;
}

int main(){
    Verb avoir("avoir",{
            "ai","as","a",              // Indicatif présent
            "avons","avez","ont",
            "eus","eus","eut",          // Passé simple
            "eûmes","eûtes","eurent",
            "aurai", "auras", "aura",
            "aurons", "aurez", "auront"
            });
    printVerbTable(avoir);
    return 0;
}