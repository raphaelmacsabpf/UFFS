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
		[Embed(source = "assets/enemy.png")] public var ASSET_ENEMY1:Class;
		[Embed(source = "assets/enemytop.png")] public var ASSET_ENEMYTOP:Class;
		[Embed(source = "assets/enemyleft.png")] public var ASSET_ENEMYLEFT:Class;
		[Embed(source = "assets/enemyright.png")] public var ASSET_ENEMYRIGHT:Class;
		private var health:int;
		/*
		0 = BOTTON
		1 = TOP
		2 = LEFT
		3 = RIGHT
		*/
		
		public function Enemy(p:FlxPoint,size:String,visible:Boolean,angle:uint) 
		{
			if (angle == 0 || angle == 3)
			{
				if(angle == 0)
					loadGraphic(ASSET_ENEMY1, true, false, 123, 121);
				else
					loadGraphic(ASSET_ENEMYRIGHT, true, false, 125, 121);
				addAnimation("size7", [0]);
				addAnimation("size6", [1]);
				addAnimation("size5", [2]);
				addAnimation("size4", [3]);
				addAnimation("size3", [4]);
				addAnimation("size2", [5]);
				addAnimation("size1", [6]);
			}
			else
			{
				if(angle == 1)
					loadGraphic(ASSET_ENEMYTOP, true, false, 121, 123);
				else
					loadGraphic(ASSET_ENEMYLEFT, true, false, 125, 121);
				addAnimation("size7", [6]);
				addAnimation("size6", [5]);
				addAnimation("size5", [4]);
				addAnimation("size4", [3]);
				addAnimation("size3", [2]);
				addAnimation("size2", [1]);
				addAnimation("size1", [0]);
			}
			if(visible == true)
				play(size);
			else
			{
				this.visible = false;
			}
			//this.scale = new FlxPoint(0.3, 0.3);
			if (angle == 0)
			{
				this.x = p.x;
				this.y = p.y;
			}
			else if (angle == 2)
			{
				this.x = p.x-60;
				this.y = p.y;
			}
			this.hurt( -99);
			
		}
		public static function make(x:Number, y:Number):FlxPoint
		{
			return new FlxPoint(x, y);
		}
		
	}

}