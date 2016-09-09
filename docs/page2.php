s<!DOCTYPE html>
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
							<hr>

						<h1><b>Welcome to the support</b></h1>
					<p>  Welcome to our support, if you have any question or if you see something strange,
						feel free to send us a message, we will enjoy to reply to you.</p>

						<form action="getinfo.php" method="post">
						<p>
    					<b><p>first name</p></b><input type="text" name="f_name" /></br>
    					<b><p>last name</p></b><input type="text" name="l_name" /></br>
    					<b><p>Your email</p></b><input type="email" name="email" /></br>

					  	</p>
					  	</br>
					  <textarea name="message" rows="8" cols="45">
Write your message here..
</textarea>
						</br><input type="submit" value="Send" />

						</form>
		<hr>
	</div>
			</div>
		</div>
	</body>
	<script src="http://code.jquery.com/jquery-latest.js"></script>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
	<script src="/js/bootstrap.min.js"></script>

</html>