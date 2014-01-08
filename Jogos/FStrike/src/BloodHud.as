package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class BloodHud extends FlxSprite
	{
		[Embed(source = "assets/bloodHud2.png")] public var ASSET_BLOODHUD:Class;
		public function BloodHud() 
		{
			loadGraphic(ASSET_BLOODHUD, true, false, 128, 128);
			for (var i:int = 0; i < 32; i++)
			{
				addAnimation("" + i, [i], 1, false);	
			}
			var rand:int = 32 * FlxG.random();
			this.play("" + rand);
			this.kill();
		}
		override public function update():void
		{
			this.alpha -= 0.009;
			if (this.alpha < 0.01)
				this.kill();
			super.update();
		}
	}
}