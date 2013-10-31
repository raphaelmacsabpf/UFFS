package  
{
	import org.flixel.FlxSprite;
	/**
	 * ...
	 * @author 
	 */
	public class Personagem extends FlxSprite
	{
		[Embed(source = "assets/BODY_skeleton.png")] public var ASSET_PERSONAGEM: Class;
		public function Personagem() 
		{
			loadGraphic(ASSET_PERSONAGEM, true, false, 64, 64);
			addAnimation("idle", [22, 23, 24], 10);
			play("idle");
		}
		
	}

}