#include <stdexcept>
#include "ops_generator.h"

using namespace std;

void ops_generator::run_rule() {
    switch (current_state)
    {
    case State::S:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Int:
        {
            Magazine.emplace(State::S);
            Magazine.emplace(State::I);
            Magazine.emplace(lexemeType::Int);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task6);
            break;
        }
        case lexemeType::Float:
        {
            Magazine.emplace(State::S);
            Magazine.emplace(State::I);
            Magazine.emplace(lexemeType::Float);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task7);
            break;
        }
        case lexemeType::ArrayInt:
        {
            Magazine.emplace(State::S);
            Magazine.emplace(State::P);
            Magazine.emplace(lexemeType::ArrayInt);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task8);
            break;
        }
        case lexemeType::ArrayFloat:
        {
            Magazine.emplace(State::S);
            Magazine.emplace(State::P);
            Magazine.emplace(lexemeType::ArrayFloat);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task9);
            break;
        }
        case lexemeType::Id:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(lexemeType::Semicolon);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::Assign);
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Assign);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            break;
        }
        case lexemeType::Read:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(lexemeType::Semicolon);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::Read);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Read);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Write:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(lexemeType::Semicolon);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::Write);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Write);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::If:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(State::Z);
            Magazine.emplace(State::K);
            Magazine.emplace(lexemeType::RightBrace);
            Magazine.emplace(State::Q);
            Magazine.emplace(State::A);
            Magazine.emplace(lexemeType::LeftBrace);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::C);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::If);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task3);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task1);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::While:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(lexemeType::RightBrace);
            Magazine.emplace(State::Q);
            Magazine.emplace(State::A);
            Magazine.emplace(lexemeType::LeftBrace);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::C);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::While);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task5);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task1);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task4);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::I:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Id:
        {
            Magazine.emplace(State::M);
            Magazine.emplace(lexemeType::Id);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task10);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::M:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Comma:
        {
            Magazine.emplace(State::M);
            Magazine.emplace(lexemeType::Id);
            Magazine.emplace(lexemeType::Comma);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task10);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Semicolon:
        {
            Magazine.emplace(lexemeType::Semicolon);

            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::P:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Id:
        {
            Magazine.emplace(State::N);
            Magazine.emplace(lexemeType::RightSquareBracket);
            Magazine.emplace(lexemeType::IntNumber);
            Magazine.emplace(lexemeType::LeftSquareBracket);
            Magazine.emplace(lexemeType::Id);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task11);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task10);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::N:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Comma:
        {
            Magazine.emplace(State::N);
            Magazine.emplace(lexemeType::RightSquareBracket);
            Magazine.emplace(lexemeType::IntNumber);
            Magazine.emplace(lexemeType::LeftSquareBracket);
            Magazine.emplace(lexemeType::Id);
            Magazine.emplace(lexemeType::Comma);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task11);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task10);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Semicolon:
        {
            Magazine.emplace(lexemeType::Semicolon);

            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::Q:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Id:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(lexemeType::Semicolon);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::Assign);
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Assign);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            break;
        }
        case lexemeType::Read:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(lexemeType::Semicolon);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::Read);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Read);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Write:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(lexemeType::Semicolon);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::Write);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Write);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::If:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(State::Z);
            Magazine.emplace(State::K);
            Magazine.emplace(lexemeType::RightBrace);
            Magazine.emplace(State::Q);
            Magazine.emplace(State::A);
            Magazine.emplace(lexemeType::LeftBrace);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::C);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::If);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task3);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task1);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::While:
        {
            Magazine.emplace(State::Q);
            Magazine.emplace(lexemeType::RightBrace);
            Magazine.emplace(State::Q);
            Magazine.emplace(State::A);
            Magazine.emplace(lexemeType::LeftBrace);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::C);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::While);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task5);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task1);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task4);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case State::A:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Id:
        {
            Magazine.emplace(lexemeType::Semicolon);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::Assign);
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);

            Generator.emplace(GeneratorTask::Assign);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            break;
        }
        case lexemeType::Read:
        {
            Magazine.emplace(lexemeType::Semicolon);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::Read);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Read);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Write:
        {
            Magazine.emplace(lexemeType::Semicolon);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::Write);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Write);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::If:
        {
            Magazine.emplace(State::Z);
            Magazine.emplace(State::K);
            Magazine.emplace(lexemeType::RightBrace);
            Magazine.emplace(State::Q);
            Magazine.emplace(State::A);
            Magazine.emplace(lexemeType::LeftBrace);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::C);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::If);

            Generator.emplace(GeneratorTask::Task3);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task1);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::While:
        {
            Magazine.emplace(lexemeType::RightBrace);
            Magazine.emplace(State::Q);
            Magazine.emplace(State::A);
            Magazine.emplace(lexemeType::LeftBrace);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::C);
            Magazine.emplace(lexemeType::LeftRoundBracket);
            Magazine.emplace(lexemeType::While);

            Generator.emplace(GeneratorTask::Task5);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task1);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task4);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::H:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::LeftSquareBracket:
        {
            Magazine.emplace(lexemeType::RightSquareBracket);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::LeftSquareBracket);

            Generator.emplace(GeneratorTask::Index);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case State::C:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::LeftRoundBracket:
        {
            Magazine.emplace(State::L);
            Magazine.emplace(State::U);
            Magazine.emplace(State::V);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::LeftRoundBracket);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Id:
        {
            Magazine.emplace(State::L);
            Magazine.emplace(State::U);
            Magazine.emplace(State::V);
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            break;
        }
        case lexemeType::IntNumber:
        {
            Magazine.emplace(State::L);
            Magazine.emplace(State::U);
            Magazine.emplace(State::V);
            Magazine.emplace(lexemeType::IntNumber);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::IntNumber);
            break;
        }
        case lexemeType::FloatNumber:
        {
            Magazine.emplace(State::L);
            Magazine.emplace(State::U);
            Magazine.emplace(State::V);
            Magazine.emplace(lexemeType::FloatNumber);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::FloatNumber);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::L:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Less:
        {
            Magazine.emplace(State::Z);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::Less);

            Generator.emplace(GeneratorTask::Less);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::More:
        {
            Magazine.emplace(State::Z);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::More);

            Generator.emplace(GeneratorTask::More);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Equal:
        {
            Magazine.emplace(State::Z);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::Equal);

            Generator.emplace(GeneratorTask::Equal);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::LessOrEqual:
        {
            Magazine.emplace(State::Z);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::LessOrEqual);

            Generator.emplace(GeneratorTask::LessOrEqual);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::MoreOrEqual:
        {
            Magazine.emplace(State::Z);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::MoreOrEqual);

            Generator.emplace(GeneratorTask::MoreOrEqual);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::NotEqual:
        {
            Magazine.emplace(State::Z);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::NotEqual);

            Generator.emplace(GeneratorTask::NotEqual);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::K:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Else:
        {
            Magazine.emplace(lexemeType::RightBrace);
            Magazine.emplace(State::Q);
            Magazine.emplace(State::A);
            Magazine.emplace(lexemeType::LeftBrace);
            Magazine.emplace(lexemeType::Else);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Task2);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case State::E:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::LeftRoundBracket:
        {
            Magazine.emplace(State::U);
            Magazine.emplace(State::V);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::LeftRoundBracket);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Id:
        {
            Magazine.emplace(State::U);
            Magazine.emplace(State::V);
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            break;
        }
        case lexemeType::IntNumber:
        {
            Magazine.emplace(State::U);
            Magazine.emplace(State::V);
            Magazine.emplace(lexemeType::IntNumber);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::IntNumber);
            break;
        }
        case lexemeType::FloatNumber:
        {
            Magazine.emplace(State::U);
            Magazine.emplace(State::V);
            Magazine.emplace(lexemeType::FloatNumber);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::FloatNumber);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::U:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Plus:
        {
            Magazine.emplace(State::U);
            Magazine.emplace(State::T);
            Magazine.emplace(lexemeType::Plus);

            Generator.emplace(GeneratorTask::Plus);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Minus:
        {
            Magazine.emplace(State::U);
            Magazine.emplace(State::T);
            Magazine.emplace(lexemeType::Minus);

            Generator.emplace(GeneratorTask::Minus);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case State::T:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::LeftRoundBracket:
        {
            Magazine.emplace(State::V);
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::LeftRoundBracket);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Id:
        {
            Magazine.emplace(State::V);
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            break;
        }
        case lexemeType::IntNumber:
        {
            Magazine.emplace(State::V);
            Magazine.emplace(lexemeType::IntNumber);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::IntNumber);
            break;
        }
        case lexemeType::FloatNumber:
        {
            Magazine.emplace(State::V);
            Magazine.emplace(lexemeType::FloatNumber);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::FloatNumber);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::V:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::Multiply:
        {
            Magazine.emplace(State::V);
            Magazine.emplace(State::F);
            Magazine.emplace(lexemeType::Multiply);

            Generator.emplace(GeneratorTask::Multiply);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Divide:
        {
            Magazine.emplace(State::V);
            Magazine.emplace(State::F);
            Magazine.emplace(lexemeType::Divide);

            Generator.emplace(GeneratorTask::Divide);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case State::F:
    {
        switch (current_lexeme.lexeme_type)
        {
        case lexemeType::LeftRoundBracket:
        {
            Magazine.emplace(lexemeType::RightRoundBracket);
            Magazine.emplace(State::E);
            Magazine.emplace(lexemeType::LeftRoundBracket);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::Empty);
            break;
        }
        case lexemeType::Id:
        {
            Magazine.emplace(State::H);
            Magazine.emplace(lexemeType::Id);

            Generator.emplace(GeneratorTask::Empty);
            Generator.emplace(GeneratorTask::VariableId);
            break;
        }
        case lexemeType::IntNumber:
        {
            Magazine.emplace(lexemeType::IntNumber);

            Generator.emplace(GeneratorTask::IntNumber);
            break;
        }
        case lexemeType::FloatNumber:
        {
            Magazine.emplace(lexemeType::FloatNumber);

            Generator.emplace(GeneratorTask::FloatNumber);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case State::Z:
    {
        break;
    }
    case State::Error:
    default:
        string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
        throw runtime_error(msg);
    }
}

void ops_generator::run_task() {
    switch (current_task)
    {
    case GeneratorTask::Empty:
        break;
    case GeneratorTask::VariableId:
        data.ops.emplace_back(current_lexeme.value, current_lexeme);
        break;
    case GeneratorTask::IntNumber:
    {
        int num = stoi(current_lexeme.value);
        data.ops.emplace_back(num, current_lexeme);
        break;
    }
    case GeneratorTask::FloatNumber:
    {
        double num = stod(current_lexeme.value);
        data.ops.emplace_back(num, current_lexeme);
        break;
    }
    case GeneratorTask::Read:
        data.ops.emplace_back(OpsItemOperation::Read, current_lexeme);
        break;
    case GeneratorTask::Write:
        data.ops.emplace_back(OpsItemOperation::Write, current_lexeme);
        break;
    case GeneratorTask::Plus:
        data.ops.emplace_back(OpsItemOperation::Plus, current_lexeme);
        break;
    case GeneratorTask::Minus:
        data.ops.emplace_back(OpsItemOperation::Minus, current_lexeme);
        break;
    case GeneratorTask::Multiply:
        data.ops.emplace_back(OpsItemOperation::Miltiply, current_lexeme);
        break;
    case GeneratorTask::Divide:
        data.ops.emplace_back(OpsItemOperation::Divide, current_lexeme);
        break;
    case GeneratorTask::Less:
        data.ops.emplace_back(OpsItemOperation::Less, current_lexeme);
        break;
    case GeneratorTask::Assign:
        data.ops.emplace_back(OpsItemOperation::Assign, current_lexeme);
        break;
    case GeneratorTask::More:
        data.ops.emplace_back(OpsItemOperation::More, current_lexeme);
        break;
    case GeneratorTask::Equal:
        data.ops.emplace_back(OpsItemOperation::Equal, current_lexeme);
        break;
    case GeneratorTask::LessOrEqual:
        data.ops.emplace_back(OpsItemOperation::LessOrEqual, current_lexeme);
        break;
    case GeneratorTask::MoreOrEqual:
        data.ops.emplace_back(OpsItemOperation::MoreOrEqual, current_lexeme);
        break;
    case GeneratorTask::NotEqual:
        data.ops.emplace_back(OpsItemOperation::NotEqual, current_lexeme);
        break;
    case GeneratorTask::Index:
        data.ops.emplace_back(OpsItemOperation::Index, current_lexeme);
        break;
    case GeneratorTask::Task1:
    {
        Marks.push(data.ops.size());
        data.ops.emplace_back(0, current_lexeme);
        data.ops.emplace_back(OpsItemOperation::JumpIfFalse, current_lexeme);
        break;
    }
    case GeneratorTask::Task2:
    {
        int place = Marks.top(); Marks.pop();
        Marks.push(data.ops.size());
        data.ops.emplace_back(0, current_lexeme);
        data.ops.emplace_back(OpsItemOperation::Jump, current_lexeme);
        data.ops[place].int_num = data.ops.size();
        break;
    }
    case GeneratorTask::Task3:
    {
        int place = Marks.top(); Marks.pop();
        data.ops[place].int_num = data.ops.size();
        break;
    }
    case GeneratorTask::Task4:
    {
        Marks.push(data.ops.size());
        break;
    }
    case GeneratorTask::Task5:
    {
        int place = Marks.top(); Marks.pop();
        data.ops.emplace_back(Marks.top(), current_lexeme); Marks.pop();
        data.ops.emplace_back(OpsItemOperation::Jump, current_lexeme);
        data.ops[place].int_num = data.ops.size();
        break;
    }
    case GeneratorTask::Task6:
    {
        current_table = table::Int;
        break;
    }
    case GeneratorTask::Task7:
    {
        current_table = table::Float;
        break;
    }
    case GeneratorTask::Task8:
    {
        current_table = table::ArrayInt;
        break;
    }
    case GeneratorTask::Task9:
    {
        current_table = table::ArrayFloat;
        break;
    }
    case GeneratorTask::Task10:
    {
        string name = current_lexeme.value;

        if (data.int_table.count(name) ||
            data.float_table.count(name) ||
            data.arrayInt_table.count(name) ||
            data.arrayFloat_table.count(name)) {
            string msg = "Redefine a variable; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }

        if (current_table == table::Int) {
            data.int_table.insert({ name, 0 });
        }
        else if (current_table == table::Float){
            data.float_table.insert({ name, 0 });
        }
        else {
            last_array_name = name;
        }

        break;
    }
    case GeneratorTask::Task11:
    {
        int size = stoi(current_lexeme.value);

        if (current_table == table::ArrayInt) {
            data.arrayInt_table.insert({ last_array_name, vector<int>(size) });
        }
        else if (current_table == table::ArrayFloat) {
            data.arrayFloat_table.insert({ last_array_name, vector<double>(size) });
        }
        else {
            string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
            throw runtime_error(msg);
        }
        
        break;
    }
    default: {
        string msg = "Generator error; line = " + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
        throw runtime_error(msg);
    }
    }
}

void ops_generator::run() {
    Magazine.emplace(State::S);
    Generator.push(GeneratorTask::Empty);

    int current_lexeme_idx = 0;
    current_lexeme = input_data[current_lexeme_idx];

    while (!Generator.empty() && !Magazine.empty())
    {
        MagazineItem current_magazine_item = Magazine.top(); Magazine.pop();
        current_state = current_magazine_item.state;
        current_task = Generator.top(); Generator.pop();
   
        run_task();

        if (current_magazine_item.is_terminal) {

            if (current_lexeme.lexeme_type == lexemeType::Finish) {
                string msg = "Generator error; All lexemes are read, BUT magazine is not empty; line = "
                    + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
                throw runtime_error(msg);
            }

            if (current_magazine_item.lexeme == current_lexeme.lexeme_type) {
                current_lexeme_idx++;
                current_lexeme = input_data[current_lexeme_idx];
            }
            else {
                string msg = "Generator error; Unexpected lexeme; line = "
                    + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
                throw runtime_error(msg);
            }
        }
        else {
            run_rule();
        }
    }

    if (current_lexeme.lexeme_type != lexemeType::Finish) {
        string msg = "There are unrecognized lexemes; line = "
            + to_string(current_lexeme.line) + ", pos = " + to_string(current_lexeme.pos);
        throw runtime_error(msg);
    }
}

InterpretData ops_generator::get_data() {
    return data;
}

ops_generator::ops_generator(vector<lexeme> lexemes) {
    input_data = lexemes;
}
