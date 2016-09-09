<!DOCTYPE html>
<html lang="fr">
	<?php include("head.php"); ?>
	<body>
	
	<?php


$mail = $_POST['email'];
if (!preg_match("#^[a-z0-9._-]+@(hotmail|live|msn).[a-z]{2,4}$#", $mail)) 
{
	$passage_ligne = "\r\n";
}
else
{
	$passage_ligne = "\n";
}
//$message_txts = "We will reply to your quesiton as soon as possible, thanks for waiting.";

$wait = $_POST['message'];

echo ($_POST['message']);

$message_txt = "salut mec first message";

$boundary = "-----=".md5(rand());

$sujet = "Support Arcade";
//=========
 
$header = "From: \"SupportArcade\"<mart_@support.com>".$passage_ligne;
$header.= "Reply-to: \"SupportArcade\" <mart_@support.com>".$passage_ligne;
$header.= "MIME-Version: 1.0".$passage_ligne;
$header.= "Content-Type: multipart/alternative;".$passage_ligne." boundary=\"$boundary\"".$passage_ligne;

$message = $passage_ligne."--".$boundary.$passage_ligne;

$message.= "Content-Type: text/plain; charset=\"ISO-8859-1\"".$passage_ligne;
$message.= "Content-Transfer-Encoding: 8bit".$passage_ligne;
$message.= "C NORMAL LA ?";

$message.= $passage_ligne."--".$boundary.$passage_ligne;

$message.= "Content-Type: text/html; charset=\"ISO-8859-1\"".$passage_ligne;
$message.= "Content-Transfer-Encoding: 8bit".$passage_ligne;
$message.= $passage_ligne.$passage_ligne;

$message.= $passage_ligne."--".$boundary."--".$passage_ligne;
$message.= $passage_ligne."--".$boundary."--".$passage_ligne;
//==========
 

mail($mail,$sujet,$message,$header);

$message = "ceci sera le deuxiéme envoi mec!";

mail($mail,$sujet,$message,$header);

header('Location: http://mart_4.shr.ovh/');


?>

























	?>

	</body>
	

</html>
