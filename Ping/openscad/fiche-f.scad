$fn=120;
difference() {
linear_extrude(height = 34.4, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-socle");
linear_extrude(height = 1.1*34.4, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-broche-f");
linear_extrude(height = 1.1*34.4, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-trou");
}

