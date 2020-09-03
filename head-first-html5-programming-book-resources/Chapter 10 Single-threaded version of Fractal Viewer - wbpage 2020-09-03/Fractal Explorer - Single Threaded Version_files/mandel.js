var canvas;
var ctx;
var rowData;
var nextRow = 0;
var generation = 0;

var i_max = 1.5;
var i_min = -1.5;
var r_min = -2.5;
var r_max = 1.5;

var max_iter = 1024;
var escape = 1025;
var palette = [];

window.onload = init;

function init() {
	canvas = document.getElementById("fractal")
	createFractal();
	resizeToWindow();
}

function computeRegion(task) {
    var iter = 0;
    var c_i = task.i;
    var max_iter = task.max_iter;
    var escape = task.escape * task.escape;
    task.values = [];
    for (var i = 0; i < task.width; i++) {
        var c_r = task.r_min + (task.r_max - task.r_min) * i / task.width;
        var z_r = 0, z_i = 0;

        for (iter = 0; z_r*z_r + z_i*z_i < escape && iter < max_iter; iter++) {
            // z -> z^2 + c
            var tmp = z_r*z_r - z_i*z_i + c_r;
            z_i = 2 * z_r * z_i + c_i;
            z_r = tmp;
        }
        if (iter == max_iter) {
            iter = -1;
        }
        task.values.push(iter);
    }
    return task;
}

function resizeToWindow() {
	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;
	redrawFractal();
}
    
function createFractal() {
	makePalette();

	canvas.onclick = function(event) {
		handleClick(event.x, event.y);
	};
    
	ctx = canvas.getContext("2d");
	rowData = ctx.createImageData(canvas.width, 1);

}

function drawRow(workerData) {
    var values = workerData.values;
    var pixelData = rowData.data;
    for (var i = 0; i < rowData.width; i++) {  // for each pixel in the row
		var red = i * 4;
		var green = i * 4 + 1;
		var blue = i * 4 + 2;
		var alpha = i * 4 + 3;

        pixelData[alpha] = 255; // set alpha to opaque

        if (values[i] < 0) {
            pixelData[red] = pixelData[green] = pixelData[blue] = 0;
        } else {
            var color = this.palette[values[i]];
            pixelData[red] = color[0];
            pixelData[green] = color[1];
            pixelData[blue] = color[2];
        }
    }
    ctx.putImageData(this.rowData, 0, workerData.row);
}

function redraw() { 
    canvas.onclick = null;

    setTimeout("handleRow(0);", 0);
}

function handleRow(n) {
    if (n < canvas.height) {
        var task = createTask(n);
        var row = computeRegion(task);
        drawRow(row);
        n++;
        setTimeout("handleRow(" + n + ");", 0);
    } else {
        canvas.onclick = function(event) {
         	handleClick(event.x, event.y);
        };
    }
}

function createTask(row) {
	var task = {
		row: row,				// row number we're working on
		width: rowData.width,   // width of the image
		generation: generation, // how far in we are
		r_min: r_min,
		r_max: r_max,
		i: i_max + (i_min - i_max) * row / canvas.height,
		max_iter: max_iter,
		escape: escape
	};
	return task;
}

function makePalette() {
    function wrap(x) {
        x = ((x + 256) & 0x1ff) - 256;
        if (x < 0) x = -x;
        return x;
    }
    for (i = 0; i <= this.max_iter; i++) {
        this.palette.push([wrap(7*i), wrap(5*i), wrap(11*i)]);
    }
}

function handleClick(x, y) {
	var width = r_max - r_min;
	var height = i_min - i_max;
	var click_r = r_min + width * x / canvas.width;
	var click_i = i_max + height * y / canvas.height;

	// zoom factor
	var zoom = 8; 

	r_min = click_r - width/zoom;
	r_max = click_r + width/zoom;
	i_max = click_i - height/zoom;
	i_min = click_i + height/zoom;

	redraw();
}


function redrawFractal() {
	var width = ((i_max - i_min) * canvas.width / canvas.height);
	var r_mid = (r_max + r_min) / 2;
	r_min = r_mid - width/2;
	r_max = r_mid + width/2;
	rowData = ctx.createImageData(canvas.width, 1);

	redraw();
}

