
module basicPlate(total_w,total_h,little_w,little_h)
{
	hull()
	{
		minkowski() 
		{
			cube([total_w,little_h,5], center = true);			
			cylinder(r=5,h=0.001);
		};
		minkowski() 
		{
			cube([little_w,total_h,5], center = true);
			cylinder(r=5,h=0.001);
		};
	};
}

module example006()
{
	$fn=50;
	translate([0,0,10])
	difference()
	{
		difference()
		{
			basicPlate(170,80,70,60);
			translate([0,0,0.1]) basicPlate(170-5,80-5,70-5,60-5);
		};
		cube([60,60,10], center = true);
	}
}

example006();

