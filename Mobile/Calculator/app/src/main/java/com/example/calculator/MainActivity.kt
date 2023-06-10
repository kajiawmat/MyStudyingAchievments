package com.example.calculator

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }
    
    private var isNumber=false
    private var isDotUsed=false
    private var isNotEnded=true
    private var openBracketCount=0

    private val operandList= listOf<Char>('+','-','*','/')

    private fun Prior(symb:Char): Int
    {
        return when(symb)
        {
            '+','-' -> 1
            '*','/' -> 2
            '(',')' -> 5
            else -> -1
        }
    }

    fun RPN(str:String):String?
    {
        var size: Int=0
        var stack=mutableListOf('f')
        stack.clear()
        var res: String=""
        var open:Int=0
        for(symb in str)
        {
            println("str: $res")
            println("stack: $stack")
            if((symb>='0'&& symb<='9') || symb=='.')
            {
                res+=symb
            }
            else
            {
                if(symb=='(') open++
                else res+=' '
                if(size==0)
                {
                    stack.add(symb)
                    size++
                }
                else
                {
                    if(symb!=')')
                    {
                        while(Prior(symb)<=Prior(stack[size-1]))
                        {
                            if(stack[size-1]=='(') break
                            size--
                            res+=stack[size]
                            res+=' '
                            stack.removeAt(size)
                            if(size==0) break
                        }
                        stack.add(symb)
                        size++
                    }
                    else
                    {
                        if(open==0) return null
                        while(stack[size-1]!='(')
                        {
                            size--
                            res+=stack[size]
                            res+=' '
                            stack.removeAt(size)
                        }
                        size--
                        stack.removeAt(size)
                        open--
                    }
                }
            }
        }
        while(size>0)
        {
            size--
            res+=' '
            res+=stack[size]
            stack.removeAt(size)
        }
        println("str: $str")
        println("str_new: $res")
        return res
    }

    private fun evalRPN(str:String): Double?
    {
        val list=str.split(' ')
        println(list)
        var stack=mutableListOf(0.0)
        stack.clear()
        var size=0
        for(operand in list)
        {
            if(operand.toDoubleOrNull()!=null)
            {
                stack.add(operand.toDouble())
                size++
            }
            else if(operand!="")
            {
                size--
                stack[size-1]=when(operand)
                {
                    "+" -> stack[size-1]+stack[size]
                    "-" -> stack[size-1]-stack[size]
                    "*" -> stack[size-1]*stack[size]
                    "/" -> {
                        if(stack[size]==0.0) return null
                        stack[size-1]/stack[size]
                    }
                    else -> 0.0
                }
                stack.removeAt(size)
            }
        }
        return stack[0]
    }

    private fun calculateExpression(): String {
        var expr=expressionView.text.toString()
        var rpn=RPN(expr)
        if(rpn==null) return "Некорр. выражение"
        var value=evalRPN(rpn.toString())
        if(value==null) return "Деление на 0"
        return value.toString()
    }

    fun numberInput(view: View) {
        if(isNotEnded && view is Button)
        {
            expressionView.append(view.text)
            isNumber=true
        }
    }
    fun operationInput(view: View) {
        if(isNotEnded && view is Button && isNumber)
        {
            expressionView.append(view.text)
            isNumber=false
            isDotUsed=false
        }
    }
    fun openBracketInput(view: View) {
        if(isNotEnded && view is Button && !isNumber)
        {
            expressionView.append(view.text)
            openBracketCount++
        }
    }
    fun closeBracketInput(view: View) {
        if(isNotEnded && view is Button && isNumber && openBracketCount>0)
        {
            expressionView.append(view.text)
            openBracketCount--
        }
    }
    fun equalInput(view: View) {
        if(isNotEnded && view is Button && isNumber && expressionView.text!="")
        {
            while(openBracketCount>0)
            {
                expressionView.append(")")
                openBracketCount--
            }
            if(expressionView.text.contentEquals("15.06"))
            {
                expressionView.text="Студент 3 курса\nгруппы ИП-012"
                valueView.text="Николаев А.Д."
            }
            else
            {
                valueView.text=calculateExpression()
                expressionView.append("=")
            }
            isNotEnded=false
        }
    }

    fun dotInput(view: View) {
        if(isNotEnded && view is Button && isNumber && !isDotUsed)
        {
            expressionView.append(view.text)
            isNumber=false
            isDotUsed=true
        }
    }
    fun backSpaceInput(view: View) {
        if(view is Button)
        {
            var text=expressionView.text
            val length=expressionView.length()
            if(length>0)
            {
                when(text[length-1])
                {
                    '=' -> {isNotEnded=true; valueView.text=""}
                    '.' -> {isDotUsed=false; isNumber=true}
                    in operandList -> isNumber=true
                    '(' -> openBracketCount--
                    ')' -> openBracketCount++
                }
                if(length==1 || text[length-2] in operandList || text[length-2]=='(') isNumber=false
                expressionView.text=text.subSequence(0,length-1)
            }
        }
    }
    fun clearInput(view: View) {
        expressionView.text=""
        valueView.text=""
        isNumber=false
        isDotUsed=false
        isNotEnded=true
    }

    fun Input(view: View) {}
}