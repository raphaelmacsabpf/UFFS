package  
{
	import org.flixel.FlxSprite;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Background extends FlxSprite
	{
		
		public function Background(toBePlayed:String) 
		{
			loadGraphic(Assets.BACKGROUND, true, false, 640, 481);
			addAnimation("0", [0], 1, false);
			addAnimation("1", [1], 1, false);
			addAnimation("2", [2], 1, false);
			addAnimation("3", [3], 1, false);
			addAnimation("4", [4], 1, false);
			addAnimation("5", [5], 1, false);
			addAnimation("6", [6], 1, false);
			addAnimation("7", [7], 1, false);
			addAnimation("8", [8], 1, false);
			addAnimation("9", [9], 1, false);
			play(toBePlayed);
		}
		
	}

}