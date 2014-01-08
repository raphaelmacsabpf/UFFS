package  
{
	import org.flixel.FlxSprite;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Block extends FlxSprite
	{
		
		public function Block(pX:Number,pY:Number) 
		{
			loadGraphic(Assets.BLOCK1, false, false, 16, 22);
			x = pX;
			y = pY;
		}
		
	}

}