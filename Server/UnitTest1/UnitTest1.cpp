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
            // ����� ��� ������� ParseCommand
            // ���� 1: �������� �������� ������� � ����� ����������
            string testData = "clear display/0xFFFF";
            ParsedCommand parsedCommand = ParseCommand(testData);
            Assert::AreEqual(parsedCommand.command, string("clear display"));
            Assert::AreEqual(parsedCommand.parameters.size(), size_t(1));
            Assert::AreEqual(parsedCommand.parameters[0], string("0xFFFF"));
        }
        TEST_METHOD(TestParseCommand2)
        {
            // ���� 2: �������� �������� ������� � ��������� �����������
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
            // ���� 3: �������� �������� ������� ��� / �� �������� � �����������
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
            // ���� 4: �������� �������� ������� � ��������� ����������� ���������� ������
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
            // ����� ��� ������� RecogniseCommand
            // ���� 1: �������� ������������ ������� � ����� ����������
            string testData = "clear display/0xFFFF";
            ParsedCommand parsedCommand = ParseCommand(testData);

            std::stringstream buffer;
            std::streambuf* sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            RecogniseCommand(parsedCommand);

            std::cout.rdbuf(sbuf);
            std::string output = buffer.str();

            Assert::IsTrue(output.find("�������� ������� clear display � ����������� 0xFFFF") != std::string::npos);
            Assert::IsTrue(output.find("������� ������� clear display") != std::string::npos);
        }

        TEST_METHOD(TestRecogniseCommand2)
        {
            // ���� 2: �������� ������������ �������� �������
            string testData = "draw triangle/100 100 0xFFFF";
            ParsedCommand parsedCommand = ParseCommand(testData);

            std::stringstream buffer;
            std::streambuf* sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            RecogniseCommand(parsedCommand);

            std::cout.rdbuf(sbuf);
            std::string output = buffer.str();

            Assert::IsTrue(output.find("�������� ������� draw triangle � ����������� 70 85 0xFFFF") != std::string::npos);
            Assert::IsTrue(output.find("������� ������� draw triangle") != std::string::npos);
        }

        TEST_METHOD(TestRecogniseCommand3)
        {
            // ���� 3: �������� ������������ ������� � ��������� �����������
            string testData = "fill rounded rectangle/5 10 15 20 0x07E0";
            ParsedCommand parsedCommand = ParseCommand(testData);

            std::stringstream buffer;
            std::streambuf* sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            RecogniseCommand(parsedCommand);

            std::cout.rdbuf(sbuf);
            std::string output = buffer.str();

            Assert::IsTrue(output.find("�������� ������� fill rounded rectangle � ����������� 5 10 15 20 0x07E0") != std::string::npos);
            Assert::IsTrue(output.find("������� ������� fill rounded rectangle") != std::string::npos);
        }

        TEST_METHOD(TestRecogniseCommand4)
        {
            // ���� 4: �������� ������������ ������� �������
            string testData = "fill ellipse/10 20 5 15 0x07E0";
            ParsedCommand parsedCommand = ParseCommand(testData);

            std::stringstream buffer;
            std::streambuf* sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            RecogniseCommand(parsedCommand);

            std::cout.rdbuf(sbuf);
            std::string output = buffer.str();

            Assert::IsTrue(output.find("�������� ������� fill ellipse � ����������� 10 20 5 15 0x07E0") != std::string::npos);
            Assert::IsTrue(output.find("���� ������� �� ����") != std::string::npos);
        }
    };
}
