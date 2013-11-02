package  
{
	import org.flixel.FlxPoint;
	import org.flixel.FlxSprite;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Enemy extends FlxSprite
	{
		[Embed(source = "assets/enemy1.png")] public var ASSET_ENEMY1:Class;
		private var health:int;
		public function Enemy(p:FlxPoint) 
		{
			loadGraphic(ASSET_ENEMY1, true, false, 123, 124);
			this.x = p.x;
			this.y = p.y;
		}
		
	}

}