package  
{
	import org.flixel.FlxSprite;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class World extends FlxSprite
	{
		[Embed(source = "assets/world1.png")] public var ASSET_WORLD:Class;
		public function World() 
		{
			loadGraphic(ASSET_WORLD, false, false, 640, 480);
		}
		
	}

}