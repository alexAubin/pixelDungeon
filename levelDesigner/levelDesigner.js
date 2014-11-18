

// ########################
// #  Global definitions  #
// ########################

// Map parameters
var mapWidth  = 42;
var mapHeight = 32;

var tileSize  = 16;
var tileSpace = 1;

// Map structure
var map;

// Canvas
var editorCanvas; 
var canvasContext;

// Current edit mode (drawing, erasing, object editing...)
var currentEditMode;

// Current object drawing (walls, switch, door, ...)
var currentObjectDrawing;

// Previous tile where mouse was on the map/canvas
var previousTileX = -1;
var previousTileY = -1;

// ################
// #  Init stuff  #
// ################

function init()
{
    // Get canvas from document
    editorCanvas = document.getElementById("editorCanvas");
    canvasContext = editorCanvas.getContext("2d");

    // Set editor and canvas width and height
    editorCanvas.width  = mapWidth * (tileSize + tileSpace*2);
    editorCanvas.height = mapHeight * (tileSize + tileSpace*2);

    // Init map
    map = [];
    for(var x=0 ; x < mapWidth ; x++) 
    {
        map[x] = [];
        for(var y=0; y < mapHeight ; y++) 
        {
            if ((x != 0) && (x != mapWidth -1) && (y != 0) && (y != mapHeight-1)) 
                    map[x][y] = { x: x, y: y, type: "empty"};
            else
                    map[x][y] = { x: x, y: y, type: "wall"};
            drawTile(x, y);
        }
    }

    // Init editor
    currentEditMode      = "drawWalls";
    currentObjectDrawing = "wall";

    setButtonActive(currentEditMode);
    closeAddObjectMenu();
}

// #################
// #  Editor menu  #
// #################

function changeEditorMode(event)
{
    setButtonInactive(currentEditMode);
    currentEditMode = event.target.id;
    setButtonActive(event.target.id);

    if (currentEditMode == "addObject") openAddObjectMenu();
    else closeAddObjectMenu();
}

function chooseObjectToAdd(event)
{
    closeAddObjectMenu();
}

function openAddObjectMenu(event)
{
    document.getElementById("editorAddObjectMenu").style.display = "block";
}

function closeAddObjectMenu(event)
{
    document.getElementById("editorAddObjectMenu").style.display = "none";
}

function setButtonActive(id)
{
    document.getElementById(id).className = "pure-button pure-button-active";
}

function setButtonInactive(id)
{
    document.getElementById(id).className = "pure-button";
}

// #################################
// #  Map interaction and drawing  #
// #################################

function clickHandler(event)
{
    [tileX, tileY] = getMousePosition(event);

    if (currentEditMode == "drawWalls") 
    { 
              if (map[tileX][tileY].type == "empty") map[tileX][tileY].type = "wall";
         else if (map[tileX][tileY].type == "wall" ) map[tileX][tileY].type = "empty";
    }

    drawTile(tileX,tileY);
}

function moveHandler(event)
{
    [currentTileX, currentTileY] = getMousePosition(event);

    if ((currentTileX == previousTileX) && (currentTileY == previousTileY)) return;

    drawTile(previousTileX, previousTileY);
    [previousTileX, previousTileY] = [currentTileX, currentTileY];

    [tilePositionX, tilePositionY] = getTilePosition(currentTileX, currentTileY);
    drawStroke(tilePositionX, tilePositionY);

    debug.innerHTML = "(x,y) = (" + currentTileX + "," + currentTileY + ")";
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

function getTilePosition(tileX, tileY)
{
    var tilePositionX = tileX * (tileSize + 2 * tileSpace) + tileSpace;
    var tilePositionY = tileY * (tileSize + 2 * tileSpace) + tileSpace;

    return [tilePositionX, tilePositionY];
}

function drawStroke(x,y)
{
    canvasContext.beginPath();
    canvasContext.lineWidth = "1";
    canvasContext.strokeStyle="black";
    canvasContext.rect(x,y,tileSize,tileSize);
    canvasContext.stroke();
}

function drawTile(x, y)
{
    if ((x == -1) || (y == -1)) return;

    // Get tile pixel position
    [tilePositionX, tilePositionY] = getTilePosition(x,y);

    // Erase old stuff
    canvasContext.fillStyle = "white";
    canvasContext.fillRect(tilePositionX-1,tilePositionY-1,tileSize+2,tileSize+2);

    // Print required color
    var type = map[x][y].type;

         if (type == "empty") canvasContext.fillStyle = "rgba(200,200,200,0.5)";
    else if (type == "wall")  canvasContext.fillStyle = "rgba(15,15,15,0.5)";

    canvasContext.fillRect(tilePositionX,tilePositionY,tileSize,tileSize);
}
