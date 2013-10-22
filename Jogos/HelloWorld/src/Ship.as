package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author 
	 */
	public class Ship extends FlxSprite
	{
		[Embed(source = "../assets/ship5.png")] public var SHIP5_BMP:Class;
		public function Ship(zzx:Number, zzy:Number) 
		{
			loadGraphic(SHIP5_BMP, true, false, 24, 25);
			addAnimation("idle", [0, 1, 2, 3], 60);
			addAnimation("louco", [2, 3], 60);
			addAnimation("rapido", [0, 1, 2, 3], 12);
			play("idle");
			//makeGraphic(10, 10, 0xff00ff00);
			x = zzx;
			y = zzy;
		}
		override public function update():void
		{
			super.update();
			if (Math.abs(FlxG.mouse.x - x) <= 20) {
				play("rapido");
			}
			else
				play("idle");
		}
	}

}