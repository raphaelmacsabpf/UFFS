package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Sight extends FlxSprite
	{
		[Embed(source = "assets/sight1.png")] public var ASSET_SIGHT1:Class;
		public function Sight() 
		{
			loadGraphic(ASSET_SIGHT1, 0, 0, 33, 34);
			this.x = (FlxG.width / 2)-(33/2);
			this.y = (FlxG.height / 2)-(34/2);
		}
		override public function update():void
		{
			this.x = (FlxG.mouse.x) - (33 / 2);
			this.y = (FlxG.mouse.y) - (34 / 2);
			super.update();
		}
		
	}

}