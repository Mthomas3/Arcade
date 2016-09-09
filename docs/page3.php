<!DOCTYPE html>
<html lang="fr">
	<?php include("head.php"); ?>
	<body>
		<div id="wiki">
			<div id="wiki-header">
				<div class="group-header">
					<table><tr><td><img src="http://img15.hostingpics.net/pics/275310pacman.png" width="96" height="96"></td>
					<td><a href="http://mart_4.shr.ovh/"><h1 style="color: black" class="exo-bold">Arcade Project</h1><p style="line-height: 1px">Pacman and Snake is coming soon!</p></a></td></tr></table>
				</div>
			</div>
				
			
				<div id="wiki-content-main">
					<h1><b>How to make a game?</b></h1>
					<hr>

						

					<b><p>Prequel :<br /></b>
					We will see together some explainations of some tools you will use in your library or your game.</p>
					<b><p>Class Entities :<br /></b>
					Entities represent all the entities of present in your game (player, enemies, power ...)
					<br />They are declare in 5 step: </p>
					 <ul>
					 	<li> An id</li>
                   <li> An position x and y</li>
                   <li> An angle</li>
                   <li> An Sprite</li>
                   <li> An shape that contain type and color</li>
					</ul>
						
						 <b><p>Class Map:<br /></b>
              			Map represent the map of the game
              			Map contain :<p/>
              			<ul>
                  <li> The map size</li>
                  <li> The cell size</li>
                  <li> A vector containing all the entities of the map </li>
                  <li> A vector containing all the Tiletype of the map </li>

					</ul>


					<b><p>Create library:</p></b>
					<ul>
       <li> Make your class to inherited of inteface IOInterface</li>
       <li> Use extern "C" to allow your program to find your class after the compilation of your library</li>
       <li> In your class declared privately:</li>
       <ul>
            <li> your map : arcade::Map *_map;</li>
            <li> A vector of Entities</li>
        </ul>
       <li> Initialize what you need with init()</li>
       <li> Make a fonction to create a windows in createWindows()</li>
       <li> In sendMap() you will receive the map you will save on you local _map</li>
       <li> In setEntities you will receive a vector of all your entitites you will save on your local vector of Entities</li>
       <li> In display() you will display the map. So traverses all the map and display want you want acording the entities or the TileType you find.</li>
       <li> In getEvents() you will catch all event (key)</li>
       <li> In sendScore() you will receive score to display it</li>
       <li> In destroyWindows() destroy your windows()</li>


</ul>
<p><b>Create game :</b><p>
<ul>
  <li> Make your class to inherited of inteface IGame</li>
  <li> In your class declared privately:</li>
  <ul>
    <li> your map : arcade::Map *_map</li>
    <li> your score </li>                                                                                                                                                                     
  </ul>
  <li> Initialize what you need with init() player, enemi, map ...</li>
  <li> In update make everething you need to be update</li>
  <li> In sendEvents you will receive events (key press ...)</li>
  <li> In GetMap() you will send your map</li>
  <li> In getEntities() you will send all your entities in a vector</li>
  <li> In getScore() return your score</li>
  <li> In closeGame() close your game</li>
</ul>


<p><b>Make comunication :</p></b>
<ul>
     <li>In your Core class declare an IOInterface * and an IGame * respectively _graphic and _game</li>
     <li>Load library</li>
     <li>Create instance of the library and the game</li>
     <li>In the core program load your library and call the fonction to initialiaze the windows _graphic->init() and _graphic->createWindow()</li>
     <li>Init the game with _game->init()</li>
     <li>Send the map to to the graphic part to let him initialise it : _graphic->sendMap(_game->getMap());</li>
     <li>catch event _graphic->getEvents() to send it to the game : _game->sendEvent(events);</li>
     <li>Send score to graphic : _graphic->sendScore(_game->getScore())</li>
     <li>send Entities to graphic : _graphic->setEntities(_game->getEntities())</li>
     <li>Update the game : _game->update(_time->DeltaTime);</li>
     <li>Diplay with  : _graphic->display()</li>
     
</ul>




						  	<hr>


						  	            <td><img src="http://img11.hostingpics.net/pics/6514591296602917221343980696731606006795n1.jpg" alt="second" />
<hr>
					
				</div>
			</div>
		</div>
	</body>
	<script src="http://code.jquery.com/jquery-latest.js"></script>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
	<script src="/js/bootstrap.min.js"></script>

</html>