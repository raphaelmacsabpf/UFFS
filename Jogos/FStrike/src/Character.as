package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Character extends FlxSprite
	{
		[Embed(source = "assets/weapon1.png")] public var ASSET_CHARACTER:Class;
		var sentido:int;
		var control:int;
		var mousePos:int;
		public function Character() 
		{
			loadGraphic(ASSET_CHARACTER, true, false, 206, 148);
			addAnimation("toRight", [0]);
			addAnimation("toLeft", [1]);
			this.x = (FlxG.width/2)-206;
			this.y = FlxG.height - 148;
			this.sentido = 1;
			this.control = 0;
			this.mousePos = 0;
			this.play("ToRight");
		}
		override public function update():void
		{
			var speed:Number = 0.2;
			var variation:int = 15;
			if (this.sentido == 1)
			{
				this.control ++;
				this.y += speed;
				if (this.control > variation)
				{
					this.sentido = 0;
					this.control = 0;
				}
			}
			else
			{
				this.control ++;
				this.y -= speed;
				if (this.control > variation)
				{
					this.sentido = 1;
					this.control = 0;
				}
			}
			if (mousePos == 0)
			{
				if (FlxG.mouse.x < (FlxG.width / 2)-10)
				{
					play("toLeft");
					this.x += 206;
					mousePos = 1;
				}
			}
			else
			{
				if (FlxG.mouse.x > (FlxG.width / 2)+10)
				{
					play("toRight");
					this.x -= 206;
					mousePos = 0;
				}
			}
			super.update();
		}
		
	}

}