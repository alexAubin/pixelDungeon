
//
// Parameters
//

pixel_matrix_size  = 60;
pixel_matrix_thick = 4.1;

plate_long_w  = 170;
plate_short_w = 70;
plate_long_h  = 80;
plate_short_h = 60;
plate_border_height = (12+3)/2; // At least battery_thick/2 mm for 9V case
plate_border_thickness = 5;
plate_thickness = pixel_matrix_thick; // Thickness of pixel matrix
plate_rounding_parameter = 5;

// Rendering

$fn=50;

module basicPlate(offset, thickness)
{
	hull()
	{
		minkowski() 
		{
			cube([plate_long_w+offset,plate_short_h+offset,thickness], center = true);			
			cylinder(r=plate_rounding_parameter,h=0.001);
		};
		minkowski() 
		{
			cube([plate_short_w+offset,plate_long_h+offset,thickness], center = true);
			cylinder(r=plate_rounding_parameter,h=0.001);
		};
	};
}

module topPlate()
{
	difference()
	{
		difference()
		{
			color([ 0.3, 0.3, 0.3 ]) 
			basicPlate(0,plate_border_height+plate_thickness);
			color([ 0.3, 0.6, 0.7 ]) 
			translate([0,0,plate_thickness]) 
			basicPlate(-plate_border_thickness,plate_border_height+plate_thickness);
		};

		translate([0,0,0])
		rotate([0,-180,180])
		pcb();
	}
}

module bottomPlate()
{
	difference()
	{
	difference()
	{
		color([ 0.3, 0.3, 0.3 ]) 
		basicPlate(0,plate_border_height+5);
		color([ 0.3, 0.6, 0.7 ])  
		translate([0,0,plate_border_height]) 
		basicPlate(-plate_border_height,plate_border_height*2);
	};
		translate([0,0,10])
		rotate([0,0,180])
		pcb();
	};
}

module button()
{
	translate([0,0,2])
	cube([6.5,6.5,5], center = true);
	translate([0,0,-1])
	cylinder(r=5,h=4, center = true);
}

module battery()
{
	cube([32,42,12], center = true);
}

module pcb()
{
	// Buttons
	translate([50,  0,3]) button();
	translate([70,  0,3]) button();
	translate([60, 10,3]) button();
	translate([60,-10,3]) button();
	translate([-52, 8,3]) button();
	translate([-68,-8,3]) button();

	// Screen
	translate([0,0,(pixel_matrix_thick+2)/2])
	cube([pixel_matrix_size,pixel_matrix_size,pixel_matrix_thick+2], center = true);

	// PCB plate
	translate([0,0,-1])
	basicPlate(-7,2);

	// Battery
	translate([0,0,-7])
	battery();
}

module main()
{

	rotate([0,-180,0])
	translate([0,0,0])
	topPlate();

	translate([0,0,-30])
	bottomPlate();

	rotate([0,0,180])
	color([ 0.9, 0.9, 0.9, 0.5 ])
	pcb();
}

main();

