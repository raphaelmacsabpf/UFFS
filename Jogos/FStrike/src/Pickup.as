package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	
	public class Pickup extends FlxSprite
	{
		[Embed(source = "assets/medkit.png")] public var ASSET_MEDKIT:Class;
		public var type:uint;
		public var aliveTime:Number;
		public function Pickup(type:uint) 
		{
			this.type = type;
			if (this.type == 0)
				this.loadGraphic(ASSET_MEDKIT, false, false, 26, 28);
			this.x = 630 * FlxG.random()+ 5;
			this.y = 480;
			this.velocity.y = -50;
			this.aliveTime = 0.0;
		}
		public function usePickup():void
		{
			if(this.type == 0)
				Map.player1.health += 30;
			this.kill();
		}
		override public function update():void
		{
			this.aliveTime += FlxG.elapsed;
			var at:uint = Math.floor(this.aliveTime) as uint;
			if (at % 2 == 0)
				this.velocity.x = +10;
			else
				this.velocity.x = -10;
			if (!this.onScreen() && this.y < 400)
				this.kill();
		}
	}
}