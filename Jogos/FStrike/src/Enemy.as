package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Enemy extends FlxSprite
	{
		[Embed(source = "assets/saymon.png")] public var ASSET_ENEMY1:Class;
		[Embed(source = "assets/enemytop.png")] public var ASSET_ENEMYTOP:Class;
		[Embed(source = "assets/enemyleft.png")] public var ASSET_ENEMYLEFT:Class;
		[Embed(source = "assets/enemyright.png")] public var ASSET_ENEMYRIGHT:Class;
		[Embed(source = "assets/enemyGunFire.mp3", mimeType = "audio/mpeg")] public var enemyGunFire:Class;
		[Embed(source ="assets/enemyGunFire2.mp3", mimeType = "audio/mpeg")] public var enemyGunFire2:Class;
		private var health:int;
		private var time:Number;
		private var difficulty:uint;
		/*
		0 = BOTTON
		1 = TOP
		2 = LEFT
		3 = RIGHT
		*/
		
		public function Enemy(e:EnemySpawnPoint,difficulty:uint = 50) 
		{
			this.difficulty = difficulty;
			this.time = 0.0;
			if (e.angle == 0 || e.angle == 3)
			{
				if(e.angle == 0)
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
				if(e.angle == 1)
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
			//this.scale = new FlxPoint(0.3, 0.3);
			if (e.angle == 0)
			{
				this.x = e.point.x;
				this.y = e.point.y;
			}
			else if (e.angle == 2)
			{
				this.x = e.point.x-60;
				this.y = e.point.y;
			}
			this.hurt( -99);
			play(e.size);
			
		}
		public function attack():void
		{
			Map.player1.health --;
			var volume:Number;
			volume = FlxG.random();
			if (volume < 0.5)
				volume = 0.5;
			var rand:Number = FlxG.random();
			if(rand > 0.5)
				FlxG.play(enemyGunFire, volume);
			else
				FlxG.play(enemyGunFire2, volume);
			this.time = 0.0;
			
		}
		override public function update():void
		{
			super.update();
			this.time += FlxG.elapsed;
			if (this.time > (this.difficulty*FlxG.random()))
				this.attack();

		}
		override public function kill():void
		{
			Map.player1.points ++;
			super.kill();
		}
	}

}