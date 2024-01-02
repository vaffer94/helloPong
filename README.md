# helloPong


function setup()
  {
    // FUNCTION TO INITIALIZE THE GAME
  }

function update()
  {
    // FUNCTION TO UPDATE GAME OBJECTS PER FRAME
  }

function draw()
  {
    // FUNCTION TO RENDERER GAME OBJECTS IN THE SCENE
  }
  
********************************************************

main()
{
    setup();

    // game loop
    while(true)
    {
        process_input();
        update();
        draw();
    }
}

********************************************************

For the game loop, we need to be sure that every experience has the same performance, the same update rate. How can we ensure it, independently from the hardware we are using?
