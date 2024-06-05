#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>

enum class TokenType
{
    add,
    sub,
    div,
    mul,
    int_lit,
    flaot_lit,
};

struct Token
{
    TokenType type;
    int line_num;
    std::optional<std::string> value;
};

std::ostream& operator<<(std::ostream& out, TokenType type)
{
    switch (type)
    {
        case TokenType::add:
        {
            out << "add";
            break;
        }
        case TokenType::sub:
        {
            out << "sub";
            break;
        }
        case TokenType::div:
        {
            out << "div";
            break;
        }
        case TokenType::mul:
        {
            out << "mul";
            break;
        }
    }

    return out;
}


struct InterNode
{
    TokenType op;
    Token arg1, arg2, res;
};


class Generator
{
private:

    std::vector<InterNode> code;
    std::vector<InterNode>::const_iterator iter;
    std::stringstream output;

public:

    Generator(std::vector<InterNode>& vec)
        : code(vec)
        , iter(code.begin())
    { }

    void start_gen()
    {
        output << "global _start\n\nsection .text\n_start:\n";
    }


    void end_gen()
    {
        output << "\tmov rax, 60\n\tmov rdi, 0\n\tsyscall";
    }


    std::string variable(const Token& var)
    {
        std::string value = var.value.value();
        if (var.type == TokenType::int_lit || var.type == TokenType::flaot_lit)
            value = '[' + value + ']';

        return value;
    }


    void gen_Node()
    {
        
        switch (iter->op)
        {
            case TokenType::add:
            {
                output << "\tmov rax," << variable(iter->arg1) << "\n"
                          "\tmov rbx," << variable(iter->arg2) << "\n"
                          "\tadd rax, rbx" << "\n"
                          "\tmov " << variable(iter->res) << ", rax\n";
                break;
            }
            case TokenType::sub:
            {
                output << "\tmov rax," << iter->arg1.value.value() << "\n"
                    "\tmov rbx," << iter->arg2.value.value() << "\n"
                    "\tsub rax, rbx" << "\n"
                    "\tmov " << iter->res.value.value() << ", rax\n";
                break;
            }
            case TokenType::div:
            {
                break;
            }
            case TokenType::mul:
            {
                break;
            }
            default:
            {
                std::cerr << "Unknown Token:" << iter->op;
            }
        }
        output << '\n';
    }

    std::string generate()
    {
        start_gen();

        for (; iter != code.end(); ++iter)
            gen_Node();

        end_gen();
        return output.str();
    }


};



int main()
{
    std::cout << "\nstart\n";
    std::ofstream fout("output.txt");

    if(!fout.is_open())
    {
        std::cerr << "Error of opening the file\n";
        std::exit(-1);
    }

    InterNode node1 = { TokenType::add,{TokenType::add,1, "1"}, {TokenType::add,1, "2"}, {TokenType::int_lit, 1, "x"} };    // x = 1 + 2
    InterNode node2 = { TokenType::add,{TokenType::add,1, "3"}, {TokenType::add,1, "4"}, {TokenType::int_lit, 1, "y"} };    // y = 3 + 4
    InterNode node3 = { TokenType::add,{TokenType::add,1, "19"}, {TokenType::add,1, "29"}, {TokenType::int_lit, 1, "x"} };    // x = 19 + 29

    std::string out;

    std::vector<InterNode> vec = { node1, node2, node3  };

    Generator generator(vec);
    out = generator.generate();
    std::cout << out;

    fout << "section .data\n\tx dw 0\n\ty dw 0\n\n";

    fout<<out;
    fout.close();


}