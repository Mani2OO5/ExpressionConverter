// Copyright 2025 'mani arab'
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Stack
{
 private:
  static const int MaxSize = 100;
  string Data[MaxSize];
  int TopIndex;

 public:
  Stack() : TopIndex(-1) {}

  bool empty()
  {
    return TopIndex == -1;
  }
  bool full()
  {
    return TopIndex == MaxSize - 1;
  }

  void push(string value)
  {
    if (full())
    {
      cout << "StackOverFlow";
      return;
    }
    TopIndex++;
    Data[TopIndex] = value;
  }
  string pop()
  {
    if (empty())
    {
      cout << "Stack is empty" << endl;
      return "";
    }

    string Item = Data[TopIndex];
    TopIndex--;
    return Item;
  }
  string TOS()
  {
    return Data[TopIndex];
  }
};
bool isOperator(char Input)
{
  static const char Operators[7] = {'+', '-', '*', '/', '^', '(', ')'};

  for (int i = 0; i < 5; i++)
  {
    if (Operators[i] == Input)
    {
      return true;
    }
  }
  return false;
}

int Op_Weight(string Op)
{
  if (Op == "-" || Op == "+")
    return 1;
  if (Op == "*" || Op == "/")
    return 2;
  if (Op == "^")
    return 3;
}

bool Input_Check(string Input)
{
  int Operator_Counter = 0;
  int Operand_Counter = 0;
  for (int i = 0; i < Input.length(); i++)
  {
    if (isOperator(Input[i]))
      Operator_Counter++;
    else
      Operand_Counter++;
  }
  return (Operator_Counter >= Operand_Counter);
}

string Etype(string Input)
{
  bool prefix = false;
  bool postfix = false;
  int counter = 0;

  int InputSize = Input.length();

  if (isOperator(Input[0]))
  {
    prefix = true;
  }

  if ((isOperator(Input[InputSize - 1])))
  {
    postfix = true;
  }

  for (int i = 0; i < InputSize; i++)
  {
    if (isOperator(Input[i]))
    {
      counter++;
    }
  }

  if (counter == 0)
  {
    return Input;
  }

  if ((prefix && postfix) || Input_Check(Input))
  {
    return "wrong input";
  }

  if (prefix)
  {
    return "prefix";
  }
  if (postfix)
  {
    return "postfix";
  }

  return "infix";
}

bool Parenthesis_check(string &expression)
{
  if (Etype(expression) == "infix")
  {
    int check_value = 0;

    for (int i = 0; i < expression.length(); i++)
    {
      if (expression[i] == '(')
        check_value++;
      if (expression[i] == ')')
        check_value--;
      if (check_value < 0)
        return false;

      if (expression[i] == '(')
      {
        if (i + 1 < expression.length() && expression[i + 1] == ')')
          return false;
      }
    }

    if (check_value == 0)
      return true;
  }
  else
  {
    for (int i = 0; i < expression.length(); i++)
    {
      if (expression[i] == '(' || expression[i] == ')')
      {
        return false;
      }
      else
      {
        return true;
      }

    }
  }
}
string converter(string Input, string expression)
{
  string Answer;
  string FinalExpr;
  int expression_Size = expression.length();
  Stack Stack;
  string Converted_Expr = "";

  if (expression_Size < 3)
    return "";

  if (Input == "prefix")
  {
    cout << "Do you want convert to infix or postfix? ";
    getline(cin, Answer);

    if (Answer == "infix")
    {
      for (int i = expression_Size - 1; i >= 0; i--)
      {
        char currentChar = expression[i];

        if (!isOperator(currentChar))
        {
          string operand(1, currentChar);
          Stack.push((operand));
        }
        else
        {
          string operand1 = Stack.pop();
          string operand2 = Stack.pop();

          string NewExpr = "(" + operand1 + currentChar + operand2 + ")";

          Stack.push(NewExpr);
        }
      }
      FinalExpr = Stack.pop();
      return FinalExpr;
    }
    else if (Answer == "postfix")
    {
      for (int i = expression_Size - 1; i >= 0; i--)
      {
        char currentChar = expression[i];

        if (!isOperator(currentChar))
        {
          string operand(1, currentChar);
          Stack.push((operand));
        }
        else
        {
          string operand1 = Stack.pop();
          string operand2 = Stack.pop();

          string NewExpr = operand1 + operand2 + currentChar;

          Stack.push(NewExpr);
        }
      }
      FinalExpr = Stack.pop();
      return FinalExpr;
    }
    else
    {
      return "Cannot convert";
      cout << "Cannot Convert";
    }
  }
  else if (Input == "infix")
  {
    cout << "Do you want convert to prefix or postfix? ";
    getline(cin, Answer);

    if (Answer == "prefix")
    {
      reverse(expression.begin(), expression.end());

      for (int i = 0; i < expression_Size; i++)
      {
        if (expression[i] == '(')
          expression[i] = ')';
        else if (expression[i] == ')')
          expression[i] = '(';
      }

      for (int i = 0; i < expression_Size; i++)
      {
        char currentChar = expression[i];

        if (!isOperator(currentChar) &&
            currentChar != '(' && currentChar != ')')
        {
          string operand(1, currentChar);
          Converted_Expr += operand;
        }
        else
        {
          if (currentChar == '(')
          {
            Stack.push("(");
          }
          else if (currentChar == ')')
          {
            while (Stack.TOS() != "(")
            {
              Converted_Expr += Stack.pop();
            }
            Stack.pop();
          }
          else
          {
            string operation(1, currentChar);

            while (!Stack.empty() &&
                   Op_Weight(operation) < Op_Weight(Stack.TOS()))
            {
              Converted_Expr += Stack.pop();
            }
            Stack.push(operation);
          }
        }
      }

      while (!Stack.empty())
      {
        Converted_Expr += Stack.pop();
      }
      reverse(Converted_Expr.begin(), Converted_Expr.end());
      return Converted_Expr;
    }
    else if (Answer == "postfix")
    {
      for (int i = 0; i < expression_Size; i++)
      {
        char currentChar = expression[i];
        if (!isOperator(currentChar) && currentChar != '(' &&
            currentChar != ')')
        {
          string operand(1, currentChar);
          Converted_Expr += operand;
        }

        else
        {
          if (currentChar == '(')
          {
            Stack.push("(");
          }
          else if (currentChar == ')')
          {
            while (Stack.TOS() != "(")
            {
              Converted_Expr += Stack.pop();
            }
            Stack.pop();
          }
          else
          {
            string operation(1, currentChar);

            while (!Stack.empty() &&
                   Op_Weight(operation) <= Op_Weight(Stack.TOS()))
            {
              Converted_Expr += Stack.pop();
            }
            Stack.push(operation);
          }
        }
      }
      while (!Stack.empty())
      {
        Converted_Expr += Stack.pop();
      }
      return Converted_Expr;
    }
    else
    {
      return "Cannot convert";
      cout << "Cannot Convert";
    }
  }
  else if (Input == "postfix")
  {
    cout << "Do you want convert to infix or prefix? ";
    getline(cin, Answer);

    if (Answer == "infix")
    {
      for (int i = 0; i < expression_Size; i++)
      {
        char currentChar = expression[i];
        if (!isOperator(currentChar))
        {
          string operand(1, currentChar);
          Stack.push((operand));
        }
        else
        {
          string operand2 = Stack.pop();
          string operand1 = Stack.pop();

          string NewExpr = "(" + operand1 + currentChar + operand2 + ")";

          Stack.push(NewExpr);
        }
      }
      FinalExpr = Stack.pop();
      return FinalExpr;
    }
    else if (Answer == "prefix")
    {
      for (int i = 0; i < expression_Size; i++)
      {
        char currentChar = expression[i];

        if (!isOperator(currentChar))
        {
          string operand(1, currentChar);
          Stack.push((operand));
        }
        else
        {
          string operand2 = Stack.pop();
          string operand1 = Stack.pop();

          string NewExpr = currentChar + operand1 + operand2;

          Stack.push(NewExpr);
        }
      }
      FinalExpr = Stack.pop();
      return FinalExpr;
    }
  }
  else
  {
    return "Wrong Input";
  }
}

int main()
{
  while (true)
  {
    string Input;
    string Ans;
    cout << "insert the expression: ";
    getline(cin, Input);

    if (!Parenthesis_check(Input))
    {
      cout << "Wrong Input" << endl;
      continue;
    }
    cout << Etype(Input) << endl;
    cout << converter(Etype(Input), Input) << endl;
  }
}
