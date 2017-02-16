package com.whf.pilin.adapter.guide;

import java.util.List;

import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.View;
import android.view.ViewGroup;

public class GuideAdapter extends PagerAdapter {
	
	private List<View> views;
	
	public GuideAdapter(List<View> views){
		
		this.views = views;
		
	}
	
	@Override
	public Object instantiateItem(ViewGroup container, int position) {
		
		((ViewPager)container).addView(views.get(position));
		
		return views.get(position);
		
	}
	@Override
	public void destroyItem(ViewGroup container, int position, Object object) {
		
		((ViewPager)container).removeView(views.get(position));
		
	}
	@Override
	public int getCount() {
		return views.size();
	}

	@Override
	public boolean isViewFromObject(View view, Object obj) {
		
		return view == obj;
	}

}
