#include <iostream>
#include <fstream>
#include <regex>
#include <set>
#include <map>

bool exist(const std::string &);

void count_lines_n();

void count_characters_c();

void count_numbers_dd();

void count_digits_d();

void regex_finder(const std::regex &regexp, const std::string &string);

void anagram_a(std::string input);

void palindrom_p(std::vector<std::string>);

void find_word_in_file(std::vector<std::string>, std::string);

void sorted_words_s();

void inversed_sorted_words_rs();

void switch_array(int argc, char *const *argv);

std::vector<std::string> argument_vektor;
std::string source_file;
std::string destination_file;
std::string rest_of_flags_files;
std::ifstream source_file_stream;
std::ofstream destination_file_stream;
bool flag_o = false;
bool flag_i = false;

int main(int argc, char *argv[]) {


    if (argc == 1) {
        std::cout << " Set one or more of the following flags to run the program \n\n"
                     "-f : Insert your text file path after this flag in order to work with it.\n For example:"
                     "-f C:/Mydirectory/myfile \n\n"
                     "-n : Prints in your console the amount of lines found on your file \n\n"
                     "-d : Prints in your console the amount of digits found on your file.\n If your file "
                     "contains only following digits: 123n, then will show you: 3 \n\n"
                     "-dd: Prints in your console the amount of numbers found on your file.\n If your file"
                     " contains only the following number: -123, then will show you: 1 \n\n"
                     "-c: Prints in your console the amount of different characters found on your file,\nalong with the total sum and "
                     "the most repeated character. If your file contains \n only the following characters: accb, then will show you: a:1,c:2,b:1 , "
                     "total sum : 4,\nmost repeated char: c\n\n"
                     "-a : This flag needs to be the last one in the queue of flags.\n Insert a set of strings after this flag and "
                     "will check if their respective\nanagrams are found on your file. \nFor example: -f myfile.txt (...) -a ala ma kota. \n\n"
                     "-p : This flag needs to be the last one in the queue of flags.\nInsert a set of strings after this flag and "
                     "will check \nif they are palindrom and found on your file. \n For example: -f myfile.txt (...) -p ala ma kota. \n\n"
                     "-s : Prints in your console all the words of your file \nsorted alfabetically in ascending order \n\n"
                     "-rs : Prints in your console all the word of your file \nsorted alfabetically in descending order \n\n"
                     "-o : Insert a text file path after this flag and all the above flags will write their output in it,\ninstead of "
                     "printing it in your console. For example: -f myfile.txt (...) -o myOutputfile.txt \n\n"
                     "-i : Insert a file path after this flag and will add to the program arguments \nthe flags you did not indicate before."
                     "\n For example -f myfile.txt (...) -i myfile2.txt . Flags -a, -o and -p are omitted as they need\nto be set with additional parameters. \n"
                     "This mean that if we run the program exclusively with flags: -f and -i \nis equivalent to running the program with flags: -f -n -d -dd -c -s -rs";

    }


    if (argc > 1) {

        /**
         * We are choosing from the arguments the ones which are flags
         * and keeping them in a vector (argument_vektor)
         * in order to determine whether flag -p or -a is at the end of the vector or not,
         * and if yes, then be able to fetch the rest of the program arguments that follow.
         * That is because flag -p or -a must be the last "flag", but not the last "program argument".
         */
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-')
                argument_vektor.push_back(argv[i]);

        }

        /**
         * If flag_o is set to be true, then the output of functions is written into the a destination file
         * from which its path is taken from the argument found after our current index
         */
        for (int i = 1; i < argc; i++) {
            if ((argv[i][0] + argv[i][1]) == ('-' + 'o')) {
                flag_o = true;

                for (int g = 0; g < std::string(
                        argv[i + 1]).size(); g++)///< iterating char by char the program argument after -o flag
                    destination_file.push_back(argv[i +
                                                    1][g]);///<destination_file is a string. so we are building a string out of the chars

                destination_file_stream.open(
                        destination_file);///<we open the destination file using the string built as a path. In this

            }

            /**
             * This "if-statemnt" opens a file containing a set that can be potentially "the rest"
             * of the flags that will be used
             *  to replace the flags that were not marked from the user
             * by the ones found on that file.
              **/

            if ((argv[i][0] + argv[i][1]) == ('-' + 'i')) {
                for (int g = 0; g < std::string(
                        argv[i + 1]).size(); g++)///< iterating char by char the program argument after -i flag
                    rest_of_flags_files.push_back(argv[i + 1][g]);
                flag_i = true;

                std::string liner;
                std::ofstream rest_of_flags_file_ofstream(
                        rest_of_flags_files);///<on this file we keep a a set being potentially the rest of the flags

                /**
                 * Flags such as -f, -o, -i, -a or -p are not written in this file
                 * because these flags need additionally a second parameter given by the user in order to work according
                 * to the expectations.
                 */
                rest_of_flags_file_ofstream << "-n \n";
                rest_of_flags_file_ofstream << "-c \n";
                rest_of_flags_file_ofstream << "-d \n";
                rest_of_flags_file_ofstream << "-dd \n";
                rest_of_flags_file_ofstream << "-s \n";
                rest_of_flags_file_ofstream << "-rs \n";

                rest_of_flags_file_ofstream.close();

                std::ifstream rest_of_flags_file_ifstream(
                        rest_of_flags_files);///< we are reading the same file we just closed

                char *new_argv[argc +
                               6];///< we create a new array where we are going to keep all flags (+6 because we can potentially add maximum 6 new flags in the worst case)
                std::copy(argv, argv + std::min(argc, argc + 6),
                          new_argv);///< we make the copy the program argument array we already had
                int k = argc;///< we get the last index

                while (rest_of_flags_file_ifstream
                        >> liner) {/// we read that file and compare the lines (the flags wrote above) with the flags we have saved in our vector

                    if (std::find(argument_vektor.begin(), argument_vektor.end(), liner) ==
                        argument_vektor.end()) {///<if the flag was not found, then we add that flag to our vector

                        char *c = strcpy((char *) malloc(liner.length() + 1),
                                         liner.c_str()); ///< copying the string into a char pointer that will point the first element of the string
                        new_argv[k] = c;///< placing it in our new array
                        argument_vektor.push_back(c);///< updating our vector of arguments
                        k++;
                    }

                }

                switch_array(k, new_argv);

            }

        }


        if (!flag_i)

            switch_array(argc, argv);

    }
}

/**
 * This method will iterate over the program arguments
 * and switch every flag, taking into account that flag -p and -a should be the last int he queue
 * @param argc is the size of our array of char
 * @param argv : is our group of arguments, and they can differ in case we have flag -i selected or not
 */
void switch_array(int argc, char *const *argv) {

    ///this is how we can find out the position of -a and know if is the last argument or not
    int index_of_a = std::distance(argument_vektor.begin(),
                                   std::find(argument_vektor.begin(), argument_vektor.end(), "-a"));
    int index_of_p = std::distance(argument_vektor.begin(),
                                   std::find(argument_vektor.begin(), argument_vektor.end(), "-p"));

    for (int i = 1; i < argc; i++) {

        switch (argv[i][0] + argv[i][1] + argv[i][2]) {

            case '-' + 'f':
                try {
                    for (int g = 0; g < std::string(argv[i + 1]).size(); g++)
                        source_file.push_back(argv[i + 1][g]);
                    if (exist(source_file)) {

                        if (!flag_o) {
                            std::cout << source_file << " was succesfully fetched \n";
                            source_file_stream.open(source_file);
                            i++;///< we skip next iteration as we don't want to switch over our file path
                        } else {
                            destination_file_stream << source_file << " was succesfully fetched \n";
                            source_file_stream.open(source_file);
                            i++;
                        }

                    }
                } catch (
                        std::logic_error) {///< a logic error can be thrown if we try to reach an element out of array bound
                    ///which is the case when the user does not provide any file path
                    std::cout << "You did not provide any path file. Establish a correct path after the flag -f.";

                }
                break;
            case '-' + 'n':
                count_lines_n();
                break;
            case '-' + 'd':
                count_digits_d();
                break;
            case '-' + 'd' + 'd':
                count_numbers_dd();
                break;
            case '-' + 'c':
                count_characters_c();
                break;
            case '-' + 'a':
                if (index_of_a != argument_vektor.size() - 1) {///< if a is not the last flag in our queue of flags
                    std::cout << "This flag needs to be inserted as the last in your queues of flags: -a" << std::endl;
                    argument_vektor.at(
                            index_of_a) = "@";///<  in case user gives more than one -a flags ( for example -a -a -p -a )
                    /// that change of value is because we are using std::find, which only finds the first occurrence,
                    /// hence, we are modifying its value without affecting the vector size to not find it again on the next search
                    index_of_a = std::distance(argument_vektor.begin(),///< this is our next search
                                               std::find(argument_vektor.begin(), argument_vektor.end(), "-a"));
                } else if (exist(source_file) && !flag_i) {
                    for (; i < argc - 1; i++) {
                        anagram_a(argv[i + 1]);
                    }
                }


                break;
            case '-' + 'p':
                if (index_of_p != argument_vektor.size() - 1) {
                    std::cout << "This flag needs to be inserted as the last in your queues of flags: -p" << std::endl;
                    argument_vektor.at(
                            index_of_p) = "@";

                    index_of_p = std::distance(argument_vektor.begin(),
                                               std::find(argument_vektor.begin(), argument_vektor.end(),
                                                         "-p"));//find next index of p

                } else if (exist(source_file)) {
                    {
                        ///Gathering all the arguments that follow the flag -p and pushing them into a vector
                        std::vector<std::string> vector;

                        for (; i < argc - 1; i++) {
                            vector.push_back(argv[i + 1]);
                        }
                        palindrom_p(vector);

                    }
                }
                break;
            case '-' + 's':
                sorted_words_s();
                break;
            case '-' + 'r' + 's':
                inversed_sorted_words_rs();
                break;
            case '-' + 'o':
                i++; /// <omitting next iteration so that we dont switch over the destination path file
                break;
            case '-' + 'i':
                i++;///< same here
                break;

            default:
                std::cout << "The flag " << argv[i] << " was not recognized" << std::endl;

        };
    }
}

/**
 * We are getting a vector of strings and
 * removing the ones which are not palindrome.
 *
 * We check if a string is palindrom by checking only
 * until half of it and comparing with the other half
 *
 * @param vector : is the vector of the streams we have gathered from the arguments that were following the flag -p
 */
void palindrom_p(std::vector<std::string> vector) {


    std::string pal = "palindromes";///< this is only for printing purposes
    for (int i = 0; i < vector.size(); i++)
        if (!equal(vector.at(i).begin(), vector.at(i).begin() + vector.at(i).size() / 2, vector.at(i).rbegin())) {
            vector.erase(vector.begin() + i); ///< we make our pre-selection

        }
    if (!vector.empty())///< if we have at least one palindrome then we call the function to select and print the ones which are present on our file
        find_word_in_file(vector, pal);


}


/**
 * In this method we put all the words from our file in a set
 * and since set is sorted by default,
 * we can print every string on the set.
 *
 */
void sorted_words_s() {

    if (exist(source_file)) {

        ///since we read always from the same stream, it is necesary to clear it and place our "iterator" always at the begining
        source_file_stream.clear();
        source_file_stream.seekg(0);

        std::set<std::string> sorted_strings;
        std::string name;


        while (source_file_stream >> name) {
            sorted_strings.insert(name);
        }

        if (!flag_o) {///< if user did not put run the program with flag "-o" as a program argument

            std::cout << "These are all the words in your file sorted in alfabetical order: " << std::endl;
            for (const auto &n : sorted_strings) {
                std::cout << n << std::endl;
            }
        } else { ///< we do the exact same thing, except that instead of printing in the cosole, we parse it to our destination file

            destination_file_stream << "These are all the words in your file sorted in alfabetical order: "
                                    << std::endl;

            for (const auto &n : sorted_strings) ///< print sorted names
            {
                destination_file_stream << n << std::endl;
            }
        }
    }
}


/**
 * We do the same as sorted_words_s
 * in reverse order
**/
void inversed_sorted_words_rs() {

    if (exist(source_file)) {


        source_file_stream.clear();
        source_file_stream.seekg(0);

        std::set<std::string> sorted_strings;
        std::string word;

        while (source_file_stream >> word) {
            sorted_strings.insert(word);
        }

        std::set<std::string>::reverse_iterator it;
        if (!flag_o) {

            std::cout << "These are all the words in your file sorted in reversed alfabetical order: " << std::endl;

            for (it = sorted_strings.rbegin(); it != sorted_strings.rend(); ++it)///< we read the set from back to front
                std::cout << *it << '\n';
        } else {
            destination_file_stream << "These are all the words in your file sorted in reversed alfabetical order: "
                                    << std::endl;

            for (it = sorted_strings.rbegin(); it != sorted_strings.rend(); ++it)
                destination_file_stream << *it << '\n';
        }

    }
}

/**
 * This method will check line by line our file
 * and try to find each element of our vector on each of them
 * @param vector : can contain either the program arguments that follow flag -a or -p
 * @param text : can be either "anagrams" or "palindroms", depending on whether the flag was -a or -p
 */
void find_word_in_file(std::vector<std::string> vector, std::string text) {

    source_file_stream.clear();
    source_file_stream.seekg(0);

    std::string line;
    if (!flag_o) {
        std::cout << "These are the " << text << " of " << vector.at(0) << " that were found on your file: "
                  << std::endl;

        while (getline(source_file_stream, line)) {
            for (int i = 0; i < vector.size(); i++)
                if (line.find(vector.at(i)) != std::string::npos) {
                    std::cout << "[" << vector.at(i) << "]" << std::endl;
                    vector.erase(vector.begin() +
                                 i);///< we erase the element because it is enough to show one occurrance only
                }
        }
    } else {

        destination_file_stream << "These are the " << text << " of " << vector.at(0)
                                << " that were found on your file: " << std::endl;

        while (getline(source_file_stream, line)) {
            for (int i = 0; i < vector.size(); i++)
                if (line.find(vector.at(i)) != std::string::npos) {
                    destination_file_stream << "[" << vector.at(i) << "]" << std::endl;
                    vector.erase(vector.begin() + i);
                }
        }
    }
}

/**
 * In this method
 * we save all possible permutations of
 * the string passed as an argument in a vector and we pass
 * that vector to another method that will look for occurrences
 * on our file
 * @param input : can contain the program arguments that follow the flag -a
 */
void anagram_a(std::string input) {

    std::string ana = "anagrams";
    std::vector<std::string> vector;
    do {
        vector.push_back(input);
    } while (next_permutation(input.begin(), input.end()));\

    find_word_in_file(vector, ana);
}

/**
 * In this method we create a regex pattern
 * that finds any digit from 0-9
 * and then pass that pattern to another method that will
 * check if it matches with the content of our file
 */
void count_digits_d() {

    std::string digits = "digits";

    if (exist(source_file)) {
        std::regex regexp("\\d");
        regex_finder(regexp, digits);
    }

}

/**
 * This method defines a pattern
 * in between two spaces or
 * at the beggining or at the end of the line (\\b).
 * Also the pattern determines that can contain 1 or zero "-" in front
 * and can be made of one or more digits from 0-9
 */
void count_numbers_dd() {

    std::string numbers = "numbers";
    if (exist(source_file)) {
        std::regex regexp("-?\\b(\\d+)\\b");
        regex_finder(regexp, numbers);
    }


}

/**
 * This method is made to find all the occurrences of
 * a certain regex pattern in our file.
 * We are checking our file line by line and increasing a counter
 * whenever the pattern has an occurrence
 * @param regexp : our pattern
 * @param s : can be "numbers" or "digits" depending on whether flag -d or -dd was called (for printing purposes)
 */
void regex_finder(const std::regex &regexp, const std::string &s) {

    source_file_stream.clear();
    source_file_stream.seekg(0);

    std::string line;
    int c = 0;

    while (getline(source_file_stream, line)) {

        ///<the first match starting from the begining of our string until the end of our string
        std::sregex_iterator current_match(line.begin(), line.end(), regexp);

        ///<we keep track if there are more matches
        std::sregex_iterator last_match;

        ///<while the current match is not equal to the lasto ne we continue output information
        while (current_match != last_match) {
            std::smatch m = *current_match;
            current_match++;///<as we are working with an iterator, we move to the next match
            c++;
        }

    }
    if (!flag_o)
        std::cout << "The amount of " << s << " on our file is: " << c << std::endl;
    else
        destination_file_stream << "The amount of " << s << " on our file is: " << c << std::endl;

}

/**
 * In this method we are counting
 * each character without repetition.
 * We do so by mapping every character in our file to an integer value which is 0
 * by default. Each char is placed in its
 * respective char key , and while doing so
 * ,increasing by 1 its respective integer value
 *
 */
void count_characters_c() {

    if (exist(source_file)) {

        source_file_stream.clear();
        source_file_stream.seekg(0);

        std::string line;


        std::map<char, int> occurrences;///<map for counting all the occurrences

        while (source_file_stream >> line) {


            for (char c : line)
                occurrences[c] += 1;
        }

        int total_amount = 0;
        int max_number = 0;
        char max_char;
        if (!flag_o) {
            std::cout << "The amount of different letters in our file is: " << occurrences.size() << std::endl;
            for (const auto &k : occurrences) {
                std::cout << k.first << " - " << k.second << '\n';
                total_amount += k.second;
                if (k.second > max_number) {
                    max_number = k.second;
                    max_char = k.first;
                }
            }

            std::cout << "The total sum of characters in our file is :" << total_amount << '\n';
            std::cout << "The most repeated character is : " << max_char << std::endl;

        } else {
            destination_file_stream << "The amount of different characters in our file is: " << occurrences.size()
                                    << std::endl;
            for (const auto &k : occurrences) {
                destination_file_stream << k.first << " - " << k.second << '\n';
                total_amount += k.second;
                if (k.second > max_number) {
                    max_number = k.second;
                    max_char = k.first;
                }
            }
            destination_file_stream << "The total sum of characters in our file is :" << total_amount << '\n';
            destination_file_stream << "The most repeated character is : " << max_char << std::endl;

        }
    }

}

/**
 * This method will go line by line on our file and
 * while doing so, increasing a counter.
 * Since we only care about the non-empty lines
 * whenever we encounter an empty line
 * the couter will decrease
 */
void count_lines_n() {


    if (exist(source_file)) {

        source_file_stream.clear();
        source_file_stream.seekg(0);

        int count = 0;
        std::string line; // the lines
        while (source_file_stream.peek() != EOF) {
            getline(source_file_stream, line);
            count++;
            if (line == "")
                count--;
        }
        if (!flag_o)
            std::cout << "The number of lines in our file is : " << count << std::endl;

        else
            destination_file_stream << "The number of lines in our file is : " << count << std::endl;
    }
}


bool exist(const std::string &name) {

    std::ifstream file(name);
    if (!file) {     ///< If our file was not found, then exit the program
        std::cout << "The source file was not found. Establish a correct path after the flag -f. " << std::endl;
        exit(0);
    } else {
        return true;
    }

}





