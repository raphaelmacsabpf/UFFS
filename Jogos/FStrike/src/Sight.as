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
		[Embed(source = "assets/blood.png")] public var ASSET_BLOOD1:Class;
		public var center:FlxSprite;
		public function Sight() 
		{
			
			loadGraphic(ASSET_SIGHT1, 0, 0, 33, 34);
			this.x = (FlxG.width / 2)-(33/2);
			this.y = (FlxG.height / 2) - (34 / 2);
			center = new FlxSprite(this.x, this.y, ASSET_BLOOD1);
			center.scale.make(0.5, 0.5);
		}
		override public function update():void
		{
			this.x = (FlxG.mouse.x) - (33 / 2);
			this.y = (FlxG.mouse.y) - (34 / 2);
			center.x = this.x +(33/2)-4.5;
			center.y = this.y +(34 / 2)-4.5;
			super.update();
		}
		
	}

}