

// Define map parameters
var mapWidth  = 32;
var mapHeight = 32;

var tileSize  = 16;
var tileSpace = 1;
    
var map;
var editorCanvas; 
var canvas;

var previousTileX = -1;
var previousTileY = -1;

var currentMode          = "drawing";
var currentObjectDrawing = "wall";

function changeEditMode(event)
{
    document.getElementById(currentMode).className = "pure-button";
    currentMode = event.target.id;
    event.target.className = "pure-button pure-button-active";
    closeDrawingModeMenu();
}

function openDrawingModeMenu(event)
{
        document.getElementById("editorDrawingModeMenu").style.display = "block";
}

function closeDrawingModeMenu(event)
{
        document.getElementById("editorDrawingModeMenu").style.display = "none";
}

function init()
{

    editorCanvas = document.getElementById("editorCanvas");
    canvas = editorCanvas.getContext("2d");

    editorCanvas.width  = mapWidth * (tileSize + tileSpace*2);
    editorCanvas.height = mapHeight * (tileSize + tileSpace*2);
    // Create map
    map = [];
    for(var x=0 ; x < mapWidth ; x++) 
    {
        map[x] = [];
        for(var y=0; y < mapHeight ; y++) 
        {
            map[x][y] = { x: x, y: y, type: "empty"};
            drawTile(x, y);
        }
    }

    document.getElementById(currentMode).className = "pure-button pure-button-active";
    closeDrawingModeMenu();
}

function getMousePosition(event)
{
    var mouseX = event.clientX - editorCanvas.getBoundingClientRect().left;
    var mouseY = event.clientY - editorCanvas.getBoundingClientRect().top;

    var tileX = parseInt(mouseX/(tileSize + 2 * tileSpace));
    var tileY = parseInt(mouseY/(tileSize + 2 * tileSpace));

    if (tileX >= mapWidth ) tileX = -1;
    if (tileY >= mapHeight) tileY = -1;
    
    return [tileX, tileY];
    
}

function clickHandler(event)
{
    [tileX, tileY] = getMousePosition(event);

         if (currentMode == "drawing") { map[tileX][tileY].type = currentObjectDrawing;  drawTile(tileX,tileY); }
    else if (currentMode == "erase"  ) { map[tileX][tileY].type = "empty";               drawTile(tileX,tileY); }
}

function moveHandler(event)
{
    [tileX, tileY] = getMousePosition(event);

    if ((tileX == previousTileX) && (tileY == previousTileY)) return;

    var tilePositionX = previousTileX * (tileSize + 2 * tileSpace) + tileSpace;
    var tilePositionY = previousTileY * (tileSize + 2 * tileSpace) + tileSpace;

    drawTile(previousTileX, previousTileY);
    
    previousTileX = tileX;
    previousTileY = tileY;

    var tilePositionX = tileX * (tileSize + 2 * tileSpace) + tileSpace;
    var tilePositionY = tileY * (tileSize + 2 * tileSpace) + tileSpace;

    canvas.beginPath();
    canvas.lineWidth = "1";
    canvas.strokeStyle="black";
    canvas.rect(tilePositionX,tilePositionY,tileSize,tileSize);
    canvas.stroke();
    debug.innerHTML = "(x,y) = (" + tileX + "," + tileY + ")";
}

function drawTile(x, y)
{
    if (x == -1) return;
    if (y == -1) return;

    var tilePositionX = x * (tileSize + 2 * tileSpace) + tileSpace;
    var tilePositionY = y * (tileSize + 2 * tileSpace) + tileSpace;
    // Erase old stuff
    canvas.fillStyle = "white";
    canvas.fillRect(tilePositionX-1,tilePositionY-1,tileSize+2,tileSize+2);
    // Print required color
    var type = map[x][y].type;

         if (type == "empty") canvas.fillStyle = "rgba(200,200,200,0.5)";
    else if (type == "wall")  canvas.fillStyle = "rgba(15,15,15,0.5)";

    canvas.fillRect(tilePositionX,tilePositionY,tileSize,tileSize);
}
