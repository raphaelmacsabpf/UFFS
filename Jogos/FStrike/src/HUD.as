package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class HUD extends FlxSprite
	{
		[Embed(source = "assets/hud.png")] public var ASSET_HUD:Class;
		public function HUD() 
		{
			loadGraphic(ASSET_HUD, false, false, 640, 48);
			this.y = FlxG.height - 52;
			this.frameHeight = 1;
			this.frameHeight = 1;
		}
		
	}

}