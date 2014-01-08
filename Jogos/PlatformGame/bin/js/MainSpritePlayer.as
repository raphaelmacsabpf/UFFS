package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class MainSpritePlayer extends FlxSprite
	{
		public var inFloor:Boolean;
		public var MAX_GRAVITY:Number;
		public var playerObject:Player;
		public function MainSpritePlayer(pX:Number,pY:Number,p:Player) 
		{
			loadGraphic(Assets.ROBOT, true, false, 64, 68);
			this.x = pX;
			this.y = pY;
			inFloor = false;
			MAX_GRAVITY = 500;
			playerObject = p;
			this.velocity.y = MAX_GRAVITY;
		}
		public function stop():void
		{
			if(this.velocity.y > 0)
				this.velocity.y = 0;
			if (this.velocity.x != 0)
			{
				velocity.x = 0;
			}
		}
		public function collisionTop():void
		{
			FlxG.log("Colidiu no topo");
			this.velocity.y = 0;
		}
		public function collisionBottom():void
		{
			FlxG.log("Colidiu no baixo");
			this.velocity.y = 0;
			inFloor = true;
		}
		public function collisionSide():void
		{
			
		}
		override public function update():void
		{
			super.update();
			playerObject.update();
			if (!inFloor)
			{
				if(this.velocity.y < MAX_GRAVITY)
					this.velocity.y += 30 * FlxG.height * FlxG.elapsed;
			}
			else
				inFloor = false;
			if (this.y > 480)
			{
				this.y = this.height;
				this.x = FlxG.random() * FlxG.width;
			}
		}
		
	}

}