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
    multi,
    div,
    div_mod,
    minus,
    equal,
    not_equal,
    greater_than,
    smaller_than,
    greater_or_equal_than,
    smaller_or_equal_than,
    _assign,
    bitwise_and,
    bitwise_inclusive_or,
    bitwise_exclusive_or,
    bitwise_not,
    _and,
    _or,
    _not,
    shift_left,
    shift_right,
    int_lit,
    float_lit,
    _int,
    _float,
    int_decl,
    float_decl,
    func_decl,
    _return,
    call,
    empty, // Если нет аргумента
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

    case TokenType::multi:
    {
        out << "multi";
        break;
    }
    case TokenType::div:
    {
        out << "div";
        break;
    }
    case TokenType::div_mod:
    {
        out << "div_mod";
        break;
    }
    case TokenType::equal:
    {
        out << "equal";
        break;
    }
    case TokenType::not_equal:
    {
        out << "not_equal";
        break;
    }
    case TokenType::int_lit:
    {
        out << "int_lit";
        break;
    }
    case TokenType::float_lit:
    {
        out << "float_lit";
        break;
    }
    case TokenType::_int:
    {
        out << "_int";
        break;
    }
    case TokenType::_assign:
    {
        out << "_assgin";
        break;
    }
    case TokenType::bitwise_and:
    {
        out << "bitwise_and";
        break;
    }
    case TokenType::bitwise_inclusive_or:
    {
        out << "bitwise_inclusive_or";
        break;
    }
    case TokenType::bitwise_exclusive_or:
    {
        out << "bitwise_exclusive_or";
        break;
    }
    case TokenType::bitwise_not:
    {
        out << "bitwise_not";
        break;
    }
    case TokenType::_and:
    {
        out << "_and";
        break;
    }
    case TokenType::_or:
    {
        out << "_or";
        break;
    }
    case TokenType::shift_left:
    {
        out << "shift_left";
        break;
    }
    case TokenType::shift_right:
    {
        out << "shift_right";
        break;
    }
    case TokenType::greater_than:
    {
        out << "greater_than";
        break;
    }
    case TokenType::smaller_than:
    {
        out << "smaller_than";
        break;
    }
    case TokenType::greater_or_equal_than:
    {
        out << "greater_or_equal_than";
        break;
    }
    case TokenType::smaller_or_equal_than:
    {
        out << "smaller_or_equal_than";
        break;
    }
    case TokenType::minus:
    {
        out << "minus";
        break;
    }
    case TokenType::_not:
    {
        out << "_not";
        break;
    }
    case TokenType::_float:
    {
        out << "_float";
        break;
    }
    case TokenType::int_decl:
    {
        out << "int_decl";
        break;
    }
    case TokenType::float_decl:
    {
        out << "float_decl";
        break;
    }
    case TokenType::_return:
    {
        out << "_return";
        break;
    }
    case TokenType::call:
    {
        out << "call";
        break;
    }
    case TokenType::func_decl:
    {
        out << "func_decl";
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
    int float_lit_cnt;

public:

    Generator(std::vector<InterNode>& vec)
        : code(vec)
        , iter(code.begin())
        , float_lit_cnt(1)
    { }

    void start_gen()
    {
        output << "section .data\nformat_int db \"%ld\",10,0\nformat_float db \"%f\",10,0\nglobal main\nextern printf\n";
    }


    void end_gen()
    {
        output << "\tmov rax, 60\n\tmov rdi, 0\n\tsyscall";
    }


    // Обернуть в [] если это имя переменной
    std::string variable(const Token& var)
    {
        std::string value = var.value.value();
        // Вообще наш генератор подразумевает, что на входе уже нет ошибок и все типы приведены куда надо, поэтому тут ничего 
        // не кастуем а сразу тупо складываем вычитаем и тд
        if (var.type != TokenType::int_lit && var.type != TokenType::float_lit)
            value = '[' + value + ']';

        return value;
    }


    // ADDITION
    void int_add()
    {
        output << "\tmov rax," << variable(iter->arg1) << "\n"
            "\tmov rbx," << variable(iter->arg2) << "\n"
            "\tadd rax, rbx" << "\n"
            "\tmov " << variable(iter->res) << ", rax\n";
    }

    void float_add()
    {
        int lit1{}, lit2{};

        if (iter->arg1.type == TokenType::float_lit)
        {
            output << "section .data\nfloat_" << float_lit_cnt << " dq " << iter->arg1.value.value() << "\n";
            lit1 = float_lit_cnt;
            ++float_lit_cnt;
        }
        if (iter->arg2.type == TokenType::float_lit)
        {
            if (!lit1)
                output << "section .data\n";
            output << "float_" << float_lit_cnt << " dq " << iter->arg2.value.value() << "\n";
            lit2 = float_lit_cnt;
            ++float_lit_cnt;
        }

        if (lit1 || lit2)
            output << "section .text\n";


        output << "\tmovsd xmm0," << (lit1 ? "[float_" + std::to_string(lit1) + "]\n" : variable(iter->arg1) + "\n");
        output << "\tmovsd xmm1," << (lit2 ? "[float_" + std::to_string(lit2) + "]\n" : variable(iter->arg2) + "\n");
        output << "\taddsd xmm0,xmm1\n"
            "\tmovsd " << variable(iter->res) << ",xmm0\n";
    }

    // SUBTRACTION
    void int_sub()
    {
        output << "\tmov rax," << variable(iter->arg1) << "\n"
            "\tmov rbx," << variable(iter->arg2) << "\n"
            "\tsub rax, rbx" << "\n"
            "\tmov " << variable(iter->res) << ", rax\n";
    }

    void float_sub()
    {
        int lit1{}, lit2{};

        if (iter->arg1.type == TokenType::float_lit)
        {
            output << "section .data\nfloat_" << float_lit_cnt << " dq " << iter->arg1.value.value() << "\n";
            lit1 = float_lit_cnt;
            ++float_lit_cnt;
        }
        if (iter->arg2.type == TokenType::float_lit)
        {
            if (!lit1)
                output << "section .data\n";
            output << "float_" << float_lit_cnt << " dq " << iter->arg2.value.value() << "\n";
            lit2 = float_lit_cnt;
            ++float_lit_cnt;
        }

        if (lit1 || lit2)
            output << "section .text\n";


        output << "\tmovsd xmm0," << (lit1 ? "[float_" + std::to_string(lit1) + "]\n" : variable(iter->arg1) + "\n");
        output << "\tmovsd xmm1," << (lit2 ? "[float_" + std::to_string(lit2) + "]\n" : variable(iter->arg2) + "\n");
        output << "\tsubsd xmm0,xmm1\n"
            "\tmovsd " << variable(iter->res) << ",xmm0\n";
    }


    // MULTIPLICATION
    void int_mul()
    {
        output << "\tmov rax," << variable(iter->arg1) << "\n"
            "\tmov rbx," << variable(iter->arg2) << "\n"
            "\timul rbx\n"
            "\tmov " << variable(iter->res) << ", rax\n";
    }

    void float_mul()
    {
        int lit1{}, lit2{};

        if (iter->arg1.type == TokenType::float_lit)
        {
            output << "section .data\nfloat_" << float_lit_cnt << " dq " << iter->arg1.value.value() << "\n";
            lit1 = float_lit_cnt;
            ++float_lit_cnt;
        }
        if (iter->arg2.type == TokenType::float_lit)
        {
            if (!lit1)
                output << "section .data\n";
            output << "float_" << float_lit_cnt << " dq " << iter->arg2.value.value() << "\n";
            lit2 = float_lit_cnt;
            ++float_lit_cnt;
        }

        if (lit1 || lit2)
            output << "section .text\n";


        output << "\tmovsd xmm0," << (lit1 ? "[float_" + std::to_string(lit1) + "]\n" : variable(iter->arg1) + "\n");
        output << "\tmovsd xmm1," << (lit2 ? "[float_" + std::to_string(lit2) + "]\n" : variable(iter->arg2) + "\n");
        output << "\tmulsd xmm0,xmm1\n"
            "\tmovsd " << variable(iter->res) << ",xmm0\n";
    }


    // DIVISION
    void int_div()
    {
        output << "\tmov rax," << variable(iter->arg1) << "\n"
            "\tmov rbx," << variable(iter->arg2) << "\n"
            "\tidiv rbx\n"
            "\tmov " << variable(iter->res) << ", rax\n";
    }

    void float_div()
    {
        int lit1{}, lit2{};

        if (iter->arg1.type == TokenType::float_lit)
        {
            output << "section .data\nfloat_" << float_lit_cnt++ << " dq " << iter->arg1.value.value() << "\n";
            lit1 = float_lit_cnt - 1;
        }
        if (iter->arg2.type == TokenType::float_lit)
        {
            if (!lit1)
                output << "section .data\n";
            output << "float_" << float_lit_cnt++ << " dq " << iter->arg2.value.value() << "\n";
            lit2 = float_lit_cnt - 1;
        }

        if (lit1 || lit2)
            output << "section .text\n";


        output << "\tmovsd xmm0," << (lit1 ? "[float_" + std::to_string(lit1) + "]\n" : variable(iter->arg1) + "\n");
        output << "\tmovsd xmm1," << (lit2 ? "[float_" + std::to_string(lit2) + "]\n" : variable(iter->arg2) + "\n");
        output << "\tdivsd xmm0,xmm1\n"
            "\tmovsd " << variable(iter->res) << ",xmm0\n";
    }


    // ASSIGN
    void int_assign()
    {
        output << "\tmov rax," << variable(iter->arg1) << "\n"
            "\tmov " << variable(iter->res) << ",rax\n";
    }

    void float_assign()
    {
        int lit1{};
        if (iter->arg1.type == TokenType::float_lit || iter->arg1.type == TokenType::_float)
        {
            output << "section .data\nfloat_" << float_lit_cnt++ << " dq " << iter->arg1.value.value() << "\nsection .text\n";
            lit1 = float_lit_cnt - 1;
        }
        output << "\tmovsd xmm0," << (lit1 ? "[float_" + std::to_string(lit1) + "]\n" : variable(iter->arg1) + "\n");
        output << "\tmovsd " << variable(iter->res) << ",xmm0\n";
    }


    // PRINTF
    void printf_call()
    {
        // Пока что умеет печатать только 1 int либо 1 float
        if (iter->arg2.type == TokenType::_int || iter->arg2.type == TokenType::int_lit) {
            output << "\tsub rsp,8\n"
                "\tmov rax," << variable(iter->arg2) << "\n"
                "\tmov [rsp+8],rax\n"
                "\tlea rdi,[format_int]\n"
                "\tmov rsi,[rsp+8]\n"
                "\txor rax,rax\n"
                "\tcall printf\n"
                "\tadd rsp,8\n";
        }
        else {
            int lit1{};
            if (iter->arg2.type == TokenType::float_lit)
            {
                output << "section .data\nfloat_" << float_lit_cnt++ << " dq " << iter->arg2.value.value() << "\nsection .text\n";
                lit1 = float_lit_cnt - 1;
            }

            std::string name = "[" + (lit1 ? "float_" + std::to_string(lit1) + "]" : variable(iter->arg2));
            output << "\tsub rsp,8\n"
                "\tmovsd xmm0," << name << "\n"
                "\tlea rdi,[format_float]\n"
                "\tmov rax,1\n"
                "\tcall printf\n"
                "\tadd rsp,8\n";
        }
    }

    void gen_Node()
    {
        // Везде помещаю значения в оба регистра(выйгрыш в скорости), вместо 1 в регистр один в памяти

        switch (iter->op)
        {
        case TokenType::add:
        {
            ((iter->arg1.type == TokenType::_float || iter->arg1.type == TokenType::float_lit || iter->arg2.type == TokenType::_float ||
                iter->arg2.type == TokenType::float_lit) ? float_add() : int_add());
            break;
        }
        case TokenType::sub:
        {
            ((iter->arg1.type == TokenType::_float || iter->arg1.type == TokenType::float_lit || iter->arg2.type == TokenType::_float ||
                iter->arg2.type == TokenType::float_lit) ? float_sub() : int_sub());
            break;
        }
        case TokenType::multi:
        {
            ((iter->arg1.type == TokenType::_float || iter->arg1.type == TokenType::float_lit || iter->arg2.type == TokenType::_float ||
                iter->arg2.type == TokenType::float_lit) ? float_mul() : int_mul());
            break;
        }
        case TokenType::div:
        {
            ((iter->arg1.type == TokenType::_float || iter->arg1.type == TokenType::float_lit || iter->arg2.type == TokenType::_float ||
                iter->arg2.type == TokenType::float_lit) ? float_div() : int_div());
            break;
        }
        // only integer
        case TokenType::div_mod:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tidiv rbx\n"
                "\tmov " << variable(iter->res) << ", rdx\n";
            break;
        }
        case TokenType::equal:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tcmp rax,rbx\n"
                "\tmov rax,0\n"
                "\tmov rbx,1\n"
                "\tcmove rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        case TokenType::not_equal:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tcmp rax,rbx\n"
                "\tmov rax,1\n"
                "\tmov rbx,0\n"
                "\tcmove rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        case TokenType::_assign:
        {
            ((iter->arg1.type == TokenType::float_lit || iter->arg1.type == TokenType::_float || iter->res.type == TokenType::_float) ? float_assign() : int_assign());
            break;
        }
        // Only for integer
        case TokenType::bitwise_and:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tand rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        // Only for integer
        case TokenType::bitwise_inclusive_or:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tor rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        // Only for integer
        case TokenType::bitwise_exclusive_or:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\txor rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        // Only for integer
        case TokenType::bitwise_not:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tnot rax\n"
                "\tmov " << variable(iter->res) << ",rax\n";
        }
        // Only for integer
        case TokenType::_and:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tand rbx,rbx\n"
                "\tcmovz rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        // Only for integer
        case TokenType::_or:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tand rax,rax\n"
                "\tcmovz rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        // Only for integer
        case TokenType::shift_left:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tshl rax," << variable(iter->arg2) << "\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        // Only for integer
        case TokenType::shift_right:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tshr rax," << variable(iter->arg2) << "\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        case TokenType::greater_than:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tcmp rax,rbx\n"
                "\tmov rax,0\n"
                "\tmov rbx,1\n"
                "\tcmovg rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        case TokenType::smaller_than:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tcmp rax,rbx\n"
                "\tmov rax,1\n"
                "\tmov rbx,0\n"
                "\tcmovg rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        case TokenType::greater_or_equal_than:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tcmp rax,rbx\n"
                "\tmov rax,0\n"
                "\tmov rbx,1\n"
                "\tcmovge rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        case TokenType::smaller_or_equal_than:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tmov rbx," << variable(iter->arg2) << "\n"
                "\tcmp rax,rbx\n"
                "\tmov rax,1\n"
                "\tmov rbx,0\n"
                "\tcmovge rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        case TokenType::minus:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\tneg rax\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        // Only for integer
        case TokenType::_not:
        {
            output << "\tmov rax," << variable(iter->arg1) << "\n"
                "\ttest rax,rax\n"
                "\tmov rax,0\n"
                "\tmov rbx,1\n"
                "\tcmovz rax,rbx\n"
                "\tmov " << variable(iter->res) << ",rax\n";
            break;
        }
        case TokenType::int_decl:
        {
            output << "section .data\n" << iter->arg1.value.value() << " dq 0\nsection .text\n";
            break;
        }
        case TokenType::float_decl:
        {
            output << "section .data\n" << iter->arg1.value.value() << " dq 0.0\nsection .text\n";
            break;
        }
        case TokenType::_return:
        {
            if (iter->arg1.type == TokenType::_float || iter->arg1.type == TokenType::float_lit)
                output << "\tcvtsd2si rax,xmm0\n";
            else
                output << "\tmov rax," << variable(iter->arg1) << "\n";
            break;
        }
        case TokenType::call:
        {
            std::string name = iter->arg1.value.value();
            if (name == "print")
                printf_call();
            else
                output << "\tcall " << name << "\n";
            break;
        }
        case TokenType::func_decl:
        {
            output << iter->arg1.value.value() << ":\n";
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

    if (!fout.is_open())
    {
        std::cerr << "Error of opening the file\n";
        std::exit(-1);
    }

    //InterNode node0 = { TokenType::_assign,{TokenType::int_lit,1, "10"}, {TokenType::empty,1, ""}, {TokenType::_int, 1, "x"} };     // x := 10
    //InterNode node0_1 = { TokenType::_assign,{TokenType::_int,1, "y"}, {TokenType::empty,1, ""}, {TokenType::_int, 1, "x"} };       // x := y

    //// Добавим пару присвоений для тестов
    //InterNode testx = { TokenType::_assign,{TokenType::int_lit,1,"15"}, {TokenType::empty,1,""},{TokenType::_int,1,"x"} }; //x:=15
    //InterNode testy = { TokenType::_assign,{TokenType::int_lit,1,"24"}, {TokenType::empty,1,""},{TokenType::_int,1,"y"} }; //y:=24
    //InterNode testz = { TokenType::_assign,{TokenType::int_lit,1,"7"}, {TokenType::empty,1,""},{TokenType::_int,1,"z"} }; //z:=7


    //InterNode node1 = { TokenType::add,{TokenType::int_lit,1, "1"}, {TokenType::int_lit,1, "2"}, {TokenType::_int, 1, "x"} };       // x := 1 + 2
    //InterNode node1_1 = { TokenType::add,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "2"}, {TokenType::_int, 1, "x"} };        // x := y + 2
    //InterNode node1_2 = { TokenType::add,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };           // x := y + z


    //InterNode node2 = { TokenType::sub,{TokenType::int_lit,1, "3"}, {TokenType::int_lit,1, "4"}, {TokenType::_int, 1, "y"} };       // y := 3 - 4
    //InterNode node2_1 = { TokenType::sub,{TokenType::int_lit,1, "3"}, {TokenType::_int,1, "x"}, {TokenType::_int, 1, "y"} };        // y := 3 - x
    //InterNode node2_2 = { TokenType::sub,{TokenType::_int,1, "x"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "y"} };           // y := x - z


    //InterNode node3 = { TokenType::multi,{TokenType::int_lit,1, "19"}, {TokenType::int_lit,1, "29"}, {TokenType::_int, 1, "x"} };     // x := 19 * 29
    //InterNode node3_1 = { TokenType::multi,{TokenType::int_lit,1, "19"}, {TokenType::_int,1, "y"}, {TokenType::_int, 1, "x"} };       // x := 19 * y
    //InterNode node3_2 = { TokenType::multi,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };           // x := y * z


    //InterNode node4 = { TokenType::div,{TokenType::int_lit,1, "22"}, {TokenType::int_lit,1, "5"}, {TokenType::_int, 1, "x"} };      // x := 22 / 5  -> int
    //InterNode node4_1 = { TokenType::div,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "5"}, {TokenType::_int, 1, "x"} };        // x := y / 5   -> int
    //InterNode node4_2 = { TokenType::div,{TokenType::_int,1, "z"}, {TokenType::_int,1, "y"}, {TokenType::_int, 1, "x"} };           // x := z / y   -> int


    //InterNode node5 = { TokenType::div_mod,{TokenType::int_lit,1, "22"}, {TokenType::int_lit,1, "5"}, {TokenType::_int, 1, "x"} };  // x := 22 % 5
    //InterNode node5_1 = { TokenType::div_mod,{TokenType::int_lit,1, "22"}, {TokenType::_int,1, "y"}, {TokenType::_int, 1, "x"} };   // x := 22 % y
    //InterNode node5_2 = { TokenType::div_mod,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };       // x := y % z


    //InterNode node6 = { TokenType::equal,{TokenType::_int,1, "x"}, {TokenType::_int,1, "y"}, {TokenType::_int, 1, "x"} };           // x := y = x
    //InterNode node6_1 = { TokenType::equal,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "1"}, {TokenType::_int, 1, "x"} };      // x := y = 1
    //InterNode node6_2 = { TokenType::equal,{TokenType::int_lit,1, "2"}, {TokenType::int_lit,1, "3"}, {TokenType::_int, 1, "x"} };   // x := 2 = 3


    //InterNode node7 = { TokenType::not_equal,{TokenType::_int,1, "x"}, {TokenType::_int,1, "y"}, {TokenType::_int, 1, "x"} };           // x := y != x
    //InterNode node7_1 = { TokenType::not_equal,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "1"}, {TokenType::_int, 1, "x"} };      // x := y != 1
    //InterNode node7_2 = { TokenType::not_equal,{TokenType::int_lit,1, "2"}, {TokenType::int_lit,1, "3"}, {TokenType::_int, 1, "x"} };   // x := 2 != 3


    //InterNode node8 = { TokenType::bitwise_and,{TokenType::int_lit,1, "2"}, {TokenType::int_lit,1, "3"}, {TokenType::_int, 1, "x"} };   // x := 2 & 3
    //InterNode node8_1 = { TokenType::bitwise_and,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "3"}, {TokenType::_int, 1, "x"} };    // x := y & 3
    //InterNode node8_2 = { TokenType::bitwise_and,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };       // x := y & z


    //InterNode node9 = { TokenType::bitwise_inclusive_or,{TokenType::int_lit,1, "2"}, {TokenType::int_lit,1, "5"}, {TokenType::_int, 1, "x"} };  // x := 2 | 5
    //InterNode node9_1 = { TokenType::bitwise_inclusive_or,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "5"}, {TokenType::_int, 1, "x"} };   // x := y | 5
    //InterNode node9_2 = { TokenType::bitwise_inclusive_or,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };      // x := y | z


    //InterNode node10 = { TokenType::bitwise_exclusive_or,{TokenType::int_lit,1, "2"}, {TokenType::int_lit,1, "3"}, {TokenType::_int, 1, "x"} }; // x := 2 ^ 3
    //InterNode node10_1 = { TokenType::bitwise_exclusive_or,{TokenType::int_lit,1, "2"}, {TokenType::_int,1, "y"}, {TokenType::_int, 1, "x"} };  // x := 2 ^ y
    //InterNode node10_2 = { TokenType::bitwise_exclusive_or,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };     // x := y ^ z


    //InterNode node11 = { TokenType::bitwise_not,{TokenType::_int,1, "x"}, {TokenType::empty,1, ""}, {TokenType::_int, 1, "x"} };        // x := ~x
    //InterNode node11_1 = { TokenType::bitwise_not,{TokenType::int_lit,1, "5"}, {TokenType::empty,1, ""}, {TokenType::_int, 1, "x"} };   // x := ~5


    //InterNode node12 = { TokenType::_and,{TokenType::int_lit,1, "1"}, {TokenType::int_lit,1, "0"}, {TokenType::_int, 1, "x"} };  // x := 1 && 0
    //InterNode node12_1 = { TokenType::_and,{TokenType::int_lit,1, "1"}, {TokenType::_int,1, "y"}, {TokenType::_int, 1, "x"} };   // x := 1 && y
    //InterNode node12_2 = { TokenType::_and,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };      // x := y && z


    //InterNode node13 = { TokenType::_or,{TokenType::int_lit,1, "5"}, {TokenType::empty,1, ""}, {TokenType::_int, 1, "x"} };     // x := 1 || 0
    //InterNode node13_1 = { TokenType::_or,{TokenType::int_lit,1, "1"}, {TokenType::_int,1, "y"}, {TokenType::_int, 1, "x"} };   // x := 1 || y
    //InterNode node13_2 = { TokenType::_or,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };      // x := y || z


    //InterNode node14 = { TokenType::shift_left,{TokenType::int_lit,1, "1"}, {TokenType::int_lit,1, "2"}, {TokenType::_int, 1, "x"} };  // x := 1 << 2
    //InterNode node14_1 = { TokenType::shift_left,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "2"}, {TokenType::_int, 1, "x"} };   // x := y || 2
    //InterNode node14_2 = { TokenType::shift_left,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };      // x := y << z


    //InterNode node15 = { TokenType::shift_right,{TokenType::int_lit,1, "4"}, {TokenType::int_lit,1, "1"}, {TokenType::_int, 1, "x"} };  // x := 4 >> 1
    //InterNode node15_1 = { TokenType::shift_right,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "1"}, {TokenType::_int, 1, "x"} };   // x := y >> 1
    //InterNode node15_2 = { TokenType::shift_right,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };      // x := y >> z


    //InterNode node16 = { TokenType::greater_than,{TokenType::int_lit,1, "3"}, {TokenType::int_lit,1, "4"}, {TokenType::_int, 1, "x"} };     // x := 3 > 4
    //InterNode node16_1 = { TokenType::greater_than,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "4"}, {TokenType::_int, 1, "x"} };      // x := y > 4
    //InterNode node16_2 = { TokenType::greater_than,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };         // x := y > z


    //InterNode node17 = { TokenType::smaller_than,{TokenType::int_lit,1, "3"}, {TokenType::int_lit,1, "4"}, {TokenType::_int, 1, "x"} };     // x := 3 < 4
    //InterNode node17_1 = { TokenType::smaller_than,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "4"}, {TokenType::_int, 1, "x"} };      // x := y < 4
    //InterNode node17_2 = { TokenType::smaller_than,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };         // x := y < z


    //InterNode node18 = { TokenType::greater_or_equal_than,{TokenType::int_lit,1, "3"}, {TokenType::int_lit,1, "4"}, {TokenType::_int, 1, "x"} };     // x := 3 >= 4
    //InterNode node18_1 = { TokenType::greater_or_equal_than,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "4"}, {TokenType::_int, 1, "x"} };      // x := y >= 4
    //InterNode node18_2 = { TokenType::greater_or_equal_than,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };         // x := y >= z


    //InterNode node19 = { TokenType::smaller_or_equal_than,{TokenType::int_lit,1, "3"}, {TokenType::int_lit,1, "4"}, {TokenType::_int, 1, "x"} };     // x := 3 <= 4
    //InterNode node19_1 = { TokenType::smaller_or_equal_than,{TokenType::_int,1, "y"}, {TokenType::int_lit,1, "4"}, {TokenType::_int, 1, "x"} };      // x := y <= 4
    //InterNode node19_2 = { TokenType::smaller_or_equal_than,{TokenType::_int,1, "y"}, {TokenType::_int,1, "z"}, {TokenType::_int, 1, "x"} };         // x := y <= z


    //InterNode node20 = { TokenType::minus,{TokenType::int_lit,1, "10"}, {TokenType::empty,1, ""}, {TokenType::_int, 1, "x"} };     // x := -10
    //InterNode node20_1 = { TokenType::minus,{TokenType::_int,1, "y"}, {TokenType::empty,1, ""}, {TokenType::_int, 1, "x"} };       // x := -y


    //InterNode node21 = { TokenType::_not,{TokenType::int_lit,1, "0"}, {TokenType::empty,1, ""}, {TokenType::_int, 1, "x"} };    // x := !0
    //InterNode node21_1 = { TokenType::_not,{TokenType::_int,1, "y"}, {TokenType::empty,1, ""}, {TokenType::_int, 1, "x"} };     // x := !y


    //std::string out;

    //std::vector<InterNode> vec = { node0, node0_1,      testx, testy, testz,     node1,node1_1, node1_2,        node2,node2_1, node2_2,         node3, node3_1, node3_2,
    //    node4, node4_1, node4_2,         node5, node5_1, node5_2,        node6, node6_1, node6_2,        node7, node7_1, node7_2,       node8, node8_1, node8_2,
    //    node9, node9_1, node9_2,        node10, node10_1, node10_2,     node11, node11_1,       node12, node12_1, node12_2,     node13, node13_1, node13_2,
    //    node14, node14_1, node14_2,     node15, node15_1, node15_2,     node16, node16_1, node16_2,     node17, node17_1, node17_2,     node18, node18_1, node8_2,
    //    node19, node19_1, node19_2,     node20, node20_1,       node21, node21_1 };

    std::string out;

    //InterNode node0 = { TokenType::add,{TokenType::float_lit,1, "1.5"}, {TokenType::float_lit,1, "1.5"}, {TokenType::_float, 1, "x"} };     // x = 1.5 + 1.5
    //InterNode node0_1 = { TokenType::add,{TokenType::_float,1, "x"}, {TokenType::float_lit,1, "1.5"}, {TokenType::_float, 1, "x"} };        // x = x + 1.5
    //InterNode node0_2 = { TokenType::add,{TokenType::float_lit,1, "1.5"}, {TokenType::float_lit,1, "1.5"}, {TokenType::_float, 1, "x"} };   // x = 1.5 + x
    //InterNode node0_3 = { TokenType::add,{TokenType::_float,1, "x"}, {TokenType::_float,1, "x"}, {TokenType::_float, 1, "x"} };             // x = x + x

    // float x
    // void foo()
    // {
    //   x = 100.0
    // }
    // int main()
    // {
    // x = x + 1.5
    // print(x)
    // return 3
    //}


    InterNode node0 = { TokenType::int_decl, {TokenType::_float,1,"x"}, {TokenType::empty,1,""},{TokenType::empty,1,""} };
    InterNode node1 = { TokenType::func_decl, {TokenType::empty,1,"foo"}, {TokenType::empty,1,""},{TokenType::empty,1,""} };
    InterNode node2 = { TokenType::_assign, {TokenType::float_lit,1,"100.0"},{TokenType::empty,1,""},{TokenType::_float,1,"x"} };
    InterNode node3 = { TokenType::func_decl, {TokenType::empty,1,"main"}, {TokenType::empty,1,""},{TokenType::empty,1,""} };
    InterNode node4 = { TokenType::add, {TokenType::float_lit,1,"1.5"},{TokenType::_float,1,"x"},{TokenType::_float,1,"x"} };
    InterNode node5 = { TokenType::call, {TokenType::empty,1,"print"},{TokenType::int_lit,1,"15"},{TokenType::empty,1,""} };
    InterNode node6 = { TokenType::call, {TokenType::empty,1,"print"},{TokenType::_float,1,"x"},{TokenType::empty,1,""} };
    InterNode node7 = { TokenType::call, {TokenType::empty,1,"print"},{TokenType::float_lit,1,"2.5"},{TokenType::empty,1,""} };
    InterNode node8 = { TokenType::_return, {TokenType::int_lit,1,"3"},{TokenType::empty,1,""},{TokenType::empty,1,""} };

    std::vector<InterNode> vec = { node0, node1, node2, node3,node4,node5,node6,node7,node8 };
    Generator generator(vec);
    out = generator.generate();
    std::cout << out;

    fout << out;
    fout.close();


}