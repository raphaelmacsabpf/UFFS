package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Map1Scene2 extends Map
	{
		[Embed(source = "assets/worlds/map_1/scene_2/scene2.png")] var ASSET_MAP1_SCENE2:Class;
		public var spawnPointGroup:FlxGroup;
		public function Map1Scene2() 
		{
			spawnPointGroup = new FlxGroup();
			spawnPointGroup.add(new EnemySpawnPoint(new FlxPoint(300, 210), "size4", 0));

		}
		override public function create():void
		{
			super.create();
			
			
			world = new FlxSprite();
			world.loadGraphic(ASSET_MAP1_SCENE2, false, false, 640, 480);
			worldGroup.add(world);
			
			var enemysp:EnemySpawnPoint
			enemysp = spawnPointGroup.getRandom() as EnemySpawnPoint;
			enemyGroup.add(new Enemy(enemysp));
			
		}
		public function addEnemy(et:Number = 0.0):void
		{
			var enemysp:EnemySpawnPoint
			enemysp = spawnPointGroup.getRandom() as EnemySpawnPoint;
			enemyGroup.add(new Enemy(enemysp));
			this.lastTimeEnemyAdded = et;
		}
		override public function update():void
		{
			var et:Number = Math.floor(this.elapsedTime);
			var et2:uint = et as uint;
			if (et != lastTimeEnemyAdded)
			{
				if (et2 % 3 == 0)
					addEnemy(et), addEnemy(et);
				else if (et2 % 17 == 0)
				{
					pickupGroup.add(new Pickup(0));
					this.lastTimeEnemyAdded = et;
				}
			}
			player1.lastEnemyAddPoint = player1.points;
			super.update();
		}
	}

}