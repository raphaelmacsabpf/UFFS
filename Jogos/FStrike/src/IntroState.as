package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class IntroState extends FlxState
	{
		[Embed(source = "assets/brasilplayforever.png")] public var ASSET_BPF:Class;
		[Embed(source = "assets/flixellogo.png")] public var ASSET_FLIXELLOGO:Class;
		private var sprite:FlxSprite;
		private var flixelLogo:FlxSprite;
		private var state:uint;
		public function IntroState() 
		{
			this.state = 0;
			var bg:FlxSprite = new FlxSprite();
			bg.makeGraphic(640, 480, 0xffffffff);
			add(bg);
				
			sprite = new FlxSprite();
			sprite.loadGraphic(ASSET_BPF, false, false, 370, 137);
			sprite.alpha = 0.0;
			sprite.x = (FlxG.width / 2) - 370 / 2;
			sprite.y = (FlxG.height / 2) - 137 / 2;
			flixelLogo = new FlxSprite();
			flixelLogo.loadGraphic(ASSET_FLIXELLOGO, false, false, 370, 137);
			flixelLogo.alpha = 0.0;
			flixelLogo.x = (FlxG.width / 2) - 370 / 2;
			flixelLogo.y = (FlxG.height / 2) - 137 / 2;
			add(flixelLogo);
			add(sprite);
		}
		override public function update():void
		{
			if (this.state == 0)
			{
				if (sprite.alpha < 1)
				{
					sprite.alpha += 0.01;
				}
				else
					this.state = 1;
			}
			else if(this.state == 1)
				if (sprite.alpha > 0.01)
					sprite.alpha -= 0.01;
				else
					this.state = 2;
			else if (this.state == 2)
				if (flixelLogo.alpha < 1)
					flixelLogo.alpha += 0.01;
				else
					this.state = 3;

			else if(this.state == 3)
				if (flixelLogo.alpha > 0.01)
					flixelLogo.alpha -= 0.01;
				else
					FlxG.switchState(new Map1Scene2());
		}
	}

}