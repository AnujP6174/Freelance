// This header file includes one function and is used in both the cpp files.

// Function Name: isNumber();
// purpose: function to check passed argument is a number or alphabet. If the passed argument is digit then the function return true else false
// parameters: char constant
// preconditions: N/A
// returns: boolean
// side effect: N/A


using namespace std;
// will check whether passed argument is number or alphabet
bool isNumber(const string &str)
{
    for (char const &c : str)
    {
        if (std::isdigit(c) == 0)
            return false; // checking whether it is alphabet or number
    }
    return true;
}