package com.example.compas.ui.main

import android.content.Context
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentPagerAdapter
import com.example.compas.CompasView1
import com.example.compas.CompasView2
import com.example.compas.R

private val TAB_TITLES = arrayOf(
    R.string.tab_text_1,
    R.string.tab_text_2
)

/**
 * A [FragmentPagerAdapter] that returns a fragment corresponding to
 * one of the sections/tabs/pages.
 */
class SectionsPagerAdapter(private val context: Context, fm: FragmentManager) :
    FragmentPagerAdapter(fm) {

    private var compasView1= CompasView1()
    private var compasView2= CompasView2()

    override fun getItem(position: Int): Fragment {
        when(position)
        {
            0 -> return compasView1
            1 -> return compasView2
        }
        return compasView2
    }

    override fun getPageTitle(position: Int): CharSequence? {
        return context.resources.getString(TAB_TITLES[position])
    }

    override fun getCount(): Int {
        // Show 2 total pages.
        return 2
    }

    fun setDegree(current_degree: Int, rotation: Int)
    {
        compasView1.rotateCompas(current_degree,rotation)
        compasView2.rotateCompas(current_degree,rotation)
    }
}