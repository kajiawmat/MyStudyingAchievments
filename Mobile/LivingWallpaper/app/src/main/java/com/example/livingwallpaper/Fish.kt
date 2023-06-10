package com.example.livingwallpaper

import android.graphics.*
import android.view.View
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlin.math.PI
import kotlin.math.sin
import kotlin.random.Random

private val fishImages: Array<Int> = arrayOf(
    R.drawable.fish_right,
    R.drawable.fish_left
)

class Fish(val widthScreen: Float, val heightScreen: Float, val perc_min: Float, val perc_max: Float, private var bitmap: Array<Bitmap>){

    private var x_start: Float=0F
    private var x_end: Float=0F
    private var dx: Float=0F
    private var x_now: Float=0F
    private var y_now: Float=0F

    private var type: Int=0
    private var alive: Boolean=false
    private var perc_now: Float=0F

    private var matrix: Matrix=Matrix()
    private var paint: Paint=Paint()

    init {
        type= Random.nextInt(bitmap.size)
        x_start=-300F
        x_end=widthScreen+300F
        GlobalScope.launch {
            while(true)
            {
                delay(200)
                if(alive)
                {
                    moveFish()
                }
                else if(perc_now>=perc_max)
                {
                    createFish()
                }
            }
        }
    }

    private fun moveFish() {
        when(type)
        {
            0 -> {
                x_now+=dx
                if(x_now>x_end) alive=false
            }
            1 -> {
                x_now-=dx
                if(x_now<x_start) alive=false
            }
            else -> {
                x_now+=dx
                if(x_now>x_end) alive=false
            }
        }
    }

    private fun createFish() {
        dx=Random.nextFloat()*20F+10F
        y_now=heightScreen*(100F-(Random.nextFloat()*(perc_max-perc_min)+perc_min))/100F
        type=(type+1)%bitmap.size
        when(type)
        {
            0 ->{
                x_now=x_start
            }
            1 -> {
                x_now=x_end
            }
            else ->{
                x_now=x_start
            }
        }
        alive=true
    }

    fun drawFish(canvas: Canvas)
    {
        if(alive)
        {
            matrix.reset()
            matrix.setTranslate(x_now,y_now)
            matrix.preScale(300F/bitmap[type].width,300F/bitmap[type].height)
            canvas.drawBitmap(bitmap[type],matrix,paint)
        }
    }

    fun setPercent(_percent: Int) {
        perc_now=_percent.toFloat()
    }
}