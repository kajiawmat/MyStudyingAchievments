package com.example.bittles

import android.content.Context
import android.graphics.*
import android.util.Log
import android.view.DragEvent
import android.view.MotionEvent
import android.view.MotionEvent.ACTION_DOWN
import android.view.View
import android.widget.ImageView
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlin.math.*
import kotlin.random.Random

private val Frames: Array<Array<Int>> = arrayOf(
    arrayOf(
        R.drawable.redbug_000,
        R.drawable.redbug_001,
        R.drawable.redbug_002,
        R.drawable.redbug_003,
        R.drawable.redbug_004,
        R.drawable.redbug_005,
        R.drawable.redbug_006,
        R.drawable.redbug_007,
        R.drawable.redbug_008,
        R.drawable.redbug_009,
        R.drawable.redbug_010,
        R.drawable.redbug_011
    ),
    arrayOf(
        R.drawable.bluebug_000,
        R.drawable.bluebug_001,
        R.drawable.bluebug_002,
        R.drawable.bluebug_003,
        R.drawable.bluebug_004,
        R.drawable.bluebug_005,
        R.drawable.bluebug_006,
        R.drawable.bluebug_007,
        R.drawable.bluebug_008,
        R.drawable.bluebug_009,
        R.drawable.bluebug_010,
        R.drawable.bluebug_011
    )
)

class BugView(context: Context,val widthScreen: Float, val heightScreen: Float) : View(context){
    private var x_now: Float=0F
    private var y_now: Float=0F
    private var x_start: Float=0F
    private var y_start: Float=0F
    private var x_end: Float=0F
    private var y_end: Float=0F
    private var length: Float=0F

    private var angle: Float=0F
    private var speed: Float=0F
    private var freq: Float=0F
    private var ampl: Float=0F

    private var type: Int=0
    private var frame: Int=0

    private var a: Float=0F
    private var b: Float=0F

    var alive: Boolean=false

    private var matrix=Matrix()
    private var paint=Paint()

    private var score=0
    private var lives=0

    init {
        a=sqrt(2.5F)*widthScreen/2
        b=sqrt(2.5F)*heightScreen/2
        createBug()
        GlobalScope.launch {
            delay((Random.nextFloat()*4000+2000).toLong())
            while(true)
            {
                delay(100)
                if(alive)
                {
                    moveBug()
                    checkBug()
                }
                else
                {
                    delay(2000L)
                    createBug()
                }
            }
        }
    }

    private fun checkBug() {
        if(x_now>length)
        {
            alive=false
        }
    }

    private fun moveBug() {
        x_now +=speed
        if(type==1) y_now = ampl*sin(freq*x_now)
    }

    private fun createBug() {
        type= Random.nextInt(2)
        alive=true
        frame=0
        getStartEndPosition()
        x_now=0F
        y_now=0F
        length=sqrt((x_end-x_start)*(x_end-x_start)+(y_end-y_start)*(y_end-y_start))
        angle= (atan2(y_end-y_start,x_end-x_start)*180/PI).toFloat()
        if(angle<0F) angle+=360F
        getSpeed()
        getSinParam()
    }

    private fun getSinParam() {
        when(type)
        {
            0 -> {
                ampl=0F
                freq=0F
            }
            1 -> {
                ampl=Random.nextFloat()*100+50F
                freq=1/(Random.nextFloat()*200+100F)
            }
        }
    }

    private fun getSpeed() {
        when(type){
            0 -> speed=Random.nextFloat()*40F+10F
            1 -> speed= Random.nextFloat()*20F+20F
        }
    }

    private fun getAngleValue(_dx: Float, _dy: Float): Float {
        var ang:Float
        var dx=_dx
        var dy=_dy
        if (dx==0F)
        {
            if(dy<0F) return 270F
            return 90F
        }
        ang= (atan(dy/dx)*180/PI).toFloat()
        if(dx<0) ang+=180F
        else if(dy<0) ang+=360F
        return ang
    }

    private fun getStartEndPosition() {
        var mode: Int = Random.nextInt(4)
        var angle_temp: Float=getAngleValue(widthScreen,heightScreen)
        var angle_start: Float=0F
        var angle_end: Float=0F
        when(type) {
            0 ->{
                when(mode){
                    0->{
                        angle_start=Random.nextFloat()*angle_temp*0.75F+angle_temp*1.25F
                    }
                    1->{
                        angle_start=180F-(Random.nextFloat()*angle_temp*0.75F+angle_temp*1.25F)
                    }
                    2->{
                        angle_start=180F+Random.nextFloat()*angle_temp*0.75F+angle_temp*1.25F
                    }
                    3->{
                        angle_start=360F-(Random.nextFloat()*angle_temp*0.75F+angle_temp*1.25F)
                    }
                }
                angle_end=Random.nextFloat()*60F+((mode+2)%4).toFloat()*90F
            }
            1 -> {
                when(mode){
                    0->{
                        angle_start=Random.nextFloat()*angle_temp-angle_temp/2
                        if(angle_start<0F) angle_start+=360F
                        angle_end=180F+Random.nextFloat()*angle_temp*2-angle_temp
                    }
                    1->{
                        angle_start=90F-(Random.nextFloat()*90F-45F)
                        angle_end=270F-(Random.nextFloat()*150F-75F)
                    }
                    2->{
                        angle_start=180F+Random.nextFloat()*angle_temp-angle_temp/2
                        angle_end=Random.nextFloat()*angle_temp*2-angle_temp
                        if(angle_end<0F) angle_end+=360F
                    }
                    3->{
                        angle_start=270F-(Random.nextFloat()*90F-45F)
                        angle_end=90F-(Random.nextFloat()*150F-75F)
                    }
                }
            }
        }
        x_start= (a*cos(angle_start/180*PI)+widthScreen/2).toFloat()
        y_start= -(b*sin(angle_start/180*PI)-heightScreen/2).toFloat()
        x_end= (a*cos(angle_end/180*PI)+widthScreen/2).toFloat()
        y_end= -(b*sin(angle_end/180*PI)-heightScreen/2).toFloat()
    }

    /*fun getStartEndPosition()
    {
        when(type)
        {
            0->{
                x_start=-widthScreen*0.5F
                x_end=widthScreen*1.5F
                y_start=Random.nextFloat()*heightScreen
                y_end=Random.nextFloat()*heightScreen
            }
            1->{
                y_start=heightScreen*1.5F
                y_end=-heightScreen*0.5F
                x_start=Random.nextFloat()*widthScreen
                x_end=Random.nextFloat()*widthScreen
            }
        }
    }*/

    fun Frame(): Bitmap
    {
        if(alive) frame=(frame+1)% Frames[type].size
        return BitmapFactory.decodeResource(resources, Frames[type][frame])
    }

    fun AngleFrame(): Float {
        when(type)
        {
            0->return 90F
            1-> return (90F+ atan((ampl*freq*cos(x_now*freq)).toDouble())*180F/PI).toFloat()
        }
        return 90F
    }

    override fun onDraw(canvas: Canvas?) {
        matrix.reset()
        var bitMap: Bitmap=Frame()
        var w=bitMap.width.toFloat()/2
        var h=bitMap.height.toFloat()/2
        matrix.setRotate(360F-angle,w,h)
        matrix.preTranslate(x_now,y_now)
        matrix.postTranslate(x_start-w,heightScreen-y_start-h)
        matrix.preRotate(AngleFrame(),w,h)
        var points: FloatArray = floatArrayOf(w,h)
        matrix.mapPoints(points)
        canvas!!.drawBitmap(bitMap,matrix,paint)
        x=points[0]
        y=points[1]
    }

    fun W(): Float=Frame().width.toFloat()/2
    fun H(): Float=Frame().height.toFloat()/2
}