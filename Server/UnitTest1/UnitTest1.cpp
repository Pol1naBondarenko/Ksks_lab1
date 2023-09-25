#include "pch.h"
#include "CppUnitTest.h"
#include "../Server/Server.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(Tests)
    {
    public:
        TEST_METHOD(TestParseCommand1)
        {
            // Тести для функції ParseCommand
            // Тест 1: Перевірка парсингу команди з одним параметром
            string testData = "clear display/0xFFFF";
            ParsedCommand parsedCommand = ParseCommand(testData);
            Assert::AreEqual(parsedCommand.command, string("clear display"));
            Assert::AreEqual(parsedCommand.parameters.size(), size_t(1));
            Assert::AreEqual(parsedCommand.parameters[0], string("0xFFFF"));
        }
        TEST_METHOD(TestParseCommand2)
        {
            // Тест 2: Перевірка парсингу команди з декількома параметрами
            string testData = "draw rectangle/10 20 30 40 0xF800";
            ParsedCommand parsedCommand = ParseCommand(testData);
            Assert::AreEqual(parsedCommand.command, string("draw rectangle"));
            Assert::AreEqual(parsedCommand.parameters.size(), size_t(5));
            Assert::AreEqual(parsedCommand.parameters[0], string("10"));
            Assert::AreEqual(parsedCommand.parameters[1], string("20"));
            Assert::AreEqual(parsedCommand.parameters[2], string("30"));
            Assert::AreEqual(parsedCommand.parameters[3], string("40"));
            Assert::AreEqual(parsedCommand.parameters[4], string("0xF800"));
        }
        TEST_METHOD(TestParseCommand3)
        {
            // Тест 3: Перевірка парсингу команди без / між командою і параметрами
            string testData = "draw line 5 10 15 20 0x07E0";
            ParsedCommand parsedCommand = ParseCommand(testData);
            Assert::AreEqual(parsedCommand.command, string("draw line"));
            Assert::AreEqual(parsedCommand.parameters.size(), size_t(5));
            Assert::AreEqual(parsedCommand.parameters[0], string("5"));
            Assert::AreEqual(parsedCommand.parameters[1], string("10"));
            Assert::AreEqual(parsedCommand.parameters[2], string("15"));
            Assert::AreEqual(parsedCommand.parameters[3], string("20"));
            Assert::AreEqual(parsedCommand.parameters[4], string("0x07E0"));
        }
        TEST_METHOD(TestParseCommand4)
        {
            // Тест 4: Перевірка парсингу команди з декількома параметрами розділеними комами
            string testData = "fill rounded rectangle/5, 10, 15, 20, 0x07E0";
            ParsedCommand parsedCommand = ParseCommand(testData);
            Assert::AreEqual(parsedCommand.command, string("fill rounded rectangle"));
            Assert::AreEqual(parsedCommand.parameters.size(), size_t(5));
            Assert::AreEqual(parsedCommand.parameters[0], string("5"));
            Assert::AreEqual(parsedCommand.parameters[1], string("10"));
            Assert::AreEqual(parsedCommand.parameters[2], string("15"));
            Assert::AreEqual(parsedCommand.parameters[3], string("20"));
            Assert::AreEqual(parsedCommand.parameters[4], string("0x07E0"));
        }

        TEST_METHOD(TestRecogniseCommand1)
        {
            // Тести для функції RecogniseCommand
            // Тест 1: Перевірка розпізнавання команди з одним параметром
            string testData = "clear display/0xFFFF";
            ParsedCommand parsedCommand = ParseCommand(testData);

            std::stringstream buffer;
            std::streambuf* sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            RecogniseCommand(parsedCommand);

            std::cout.rdbuf(sbuf);
            std::string output = buffer.str();

            Assert::IsTrue(output.find("Отримано команду clear display з параметрами 0xFFFF") != std::string::npos);
            Assert::IsTrue(output.find("Обробка команди clear display") != std::string::npos);
        }

        TEST_METHOD(TestRecogniseCommand2)
        {
            // Тест 2: Перевірка розпізнавання неіснуючої команди
            string testData = "draw triangle/100 100 0xFFFF";
            ParsedCommand parsedCommand = ParseCommand(testData);

            std::stringstream buffer;
            std::streambuf* sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            RecogniseCommand(parsedCommand);

            std::cout.rdbuf(sbuf);
            std::string output = buffer.str();

            Assert::IsTrue(output.find("Отримано команду draw triangle з параметрами 70 85 0xFFFF") != std::string::npos);
            Assert::IsTrue(output.find("Обробка команди draw triangle") != std::string::npos);
        }

        TEST_METHOD(TestRecogniseCommand3)
        {
            // Тест 3: Перевірка розпізнавання команди з декількома параметрами
            string testData = "fill rounded rectangle/5 10 15 20 0x07E0";
            ParsedCommand parsedCommand = ParseCommand(testData);

            std::stringstream buffer;
            std::streambuf* sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            RecogniseCommand(parsedCommand);

            std::cout.rdbuf(sbuf);
            std::string output = buffer.str();

            Assert::IsTrue(output.find("Отримано команду fill rounded rectangle з параметрами 5 10 15 20 0x07E0") != std::string::npos);
            Assert::IsTrue(output.find("Обробка команди fill rounded rectangle") != std::string::npos);
        }

        TEST_METHOD(TestRecogniseCommand4)
        {
            // Тест 4: Перевірка розпізнавання існуючої команди
            string testData = "fill ellipse/10 20 5 15 0x07E0";
            ParsedCommand parsedCommand = ParseCommand(testData);

            std::stringstream buffer;
            std::streambuf* sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            RecogniseCommand(parsedCommand);

            std::cout.rdbuf(sbuf);
            std::string output = buffer.str();

            Assert::IsTrue(output.find("Отримано команду fill ellipse з параметрами 10 20 5 15 0x07E0") != std::string::npos);
            Assert::IsTrue(output.find("Такої команди не існує") != std::string::npos);
        }
    };
}
