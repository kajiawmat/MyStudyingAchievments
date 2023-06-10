package com.example.livingwallpaper

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.Path
import android.view.View
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlin.math.PI
import kotlin.math.sin

class WavePath(val widthScreen: Float, val heightScreen: Float){

    private var freq: Float=0F
    private var shift: Float=0F
    private var ampl: Float=25F
    private var per_count: Float=2F
    private var dshift: Float=2*PI.toFloat()/100F
    private var y_start: Float=0F
    private var x_start: Float=0F
    private var x_end: Float=0F
    private var dx: Float=0F
    private var frags: Float=0F

    private var fillPaint: Paint= Paint()
    private var circuitPaint: Paint=Paint()

    private var path: Path =Path()
    init {
        freq=per_count*(2*PI.toFloat()/widthScreen)
        x_start=-widthScreen/per_count
        x_end=widthScreen*(per_count+1)/per_count
        dx=1.5F*per_count/widthScreen
        frags=((per_count+2)/per_count)*widthScreen/dx
        y_start=heightScreen/2

        fillPaint.color= Color.CYAN
        fillPaint.style=Paint.Style.FILL_AND_STROKE
        fillPaint.alpha=200
        circuitPaint.color=Color.BLUE
        circuitPaint.style=Paint.Style.STROKE
        circuitPaint.strokeWidth=6F


        GlobalScope.launch {
            while(true)
            {
                delay(200)
                shift+=dshift
                if(shift>2*PI.toFloat()) shift-=2*PI.toFloat()
            }
        }
    }

    fun drawWave(canvas: Canvas)
    {
        var shift=this.shift
        path=Path()
        path.moveTo(x_start,y_start+ampl*sin(freq*x_start+shift))
        var x=x_start
        for(i in 0 until frags.toInt())
        {
            x+=dx
            path.lineTo(x,y_start+ampl*sin(freq*x+shift))
        }
        path.lineTo(x_end,heightScreen+100F)
        path.lineTo(x_start,heightScreen+100F)
        canvas.drawPath(path,fillPaint)
        //canvas.drawPath(path,circuitPaint)
    }

    fun setPercent(level: Int) {
        y_start=heightScreen*(1F-level/100F)
    }
}