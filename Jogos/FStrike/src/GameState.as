package  
{
	import org.flixel.*;
	import org.flixel.plugin.photonstorm.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class GameState extends FlxState
	{
		[Embed(source = "assets/gunfire.mp3", mimeType = "audio/mpeg")] private var gunfire:Class;
		[Embed(source = "assets/reload.mp3", mimeType = "audio/mpeg")] private var reload:Class;
		public var world:World;
		public var character:Character;
		public var sight:Sight;
		public var hud:HUD;
		public var healthText:FlxText;
		public var ammoText:FlxText;
		public var player1:Player;
		public var hudGroup:FlxGroup;
		public var enemyGroup:FlxGroup;
		public var mapGroup:FlxGroup;
		public var worldGroup:FlxGroup;
		public var shootGroup:FlxGroup;
		public var MAX_ENEMIES:uint;
		
		[Embed(source = "assets/blood.png")] public var ASSET_BLOOD1:Class;
		override public function create():void
		{
			hudGroup = new FlxGroup();
			enemyGroup = new FlxGroup();
			mapGroup = new FlxGroup();
			worldGroup = new FlxGroup();
			shootGroup = new FlxGroup();	
			
			world = new World(1,1);
			character = new Character();
			sight = new Sight();
			hud = new HUD();
			player1 = new Player();
		
			
			
			
			var strHealth = "" + player1.health;
			healthText = new FlxText(10, FlxG.height - 46, 60, strHealth);
			healthText.size = 28;
			healthText.alignment = "center";
			
			var strAmmo = player1.ammo+"/"+player1.maxAmmo;
			ammoText = new FlxText(FlxG.width-115, FlxG.height - 46, 90, strAmmo);
			ammoText.size = 28;
			ammoText.alignment = "center";
			hudGroup.add(hud);
			hudGroup.add(sight);
			hudGroup.add(sight.center);
			hudGroup.add(healthText);
			hudGroup.add(ammoText);
			worldGroup.add(world);
			
			
			
			add(worldGroup);
			add(enemyGroup);
			add(mapGroup);
			add(shootGroup);
			add(character);
			add(hudGroup);
			
			
			mapGroup.add(new MapObj(0, 0,1));
			mapGroup.add(new MapObj( -50, 0,1));
			mapGroup.add(new MapObj( -100, 0, 1));
			mapGroup.add(new MapObj(0, 0,2));
			
			enemyGroup.add(new Enemy(new FlxPoint(300, 210), "size4", true,0));
			enemyGroup.add(new Enemy(new FlxPoint(350, 210), "size4", true,0));
			enemyGroup.add(new Enemy(new FlxPoint(224, 232), "size4", true, 2));
			enemyGroup.add(new Enemy(new FlxPoint(300, 210), "size4", true,0));
			enemyGroup.add(new Enemy(new FlxPoint(350, 210), "size4", true,0));
			enemyGroup.add(new Enemy(new FlxPoint(224, 232), "size4", true, 2));
			enemyGroup.add(new Enemy(new FlxPoint(300, 210), "size4", true,0));
			enemyGroup.add(new Enemy(new FlxPoint(350, 210), "size4", true,0));
			enemyGroup.add(new Enemy(new FlxPoint(224, 232), "size4", true, 2));
			enemyGroup.add(new Enemy(new FlxPoint(300, 210), "size4", true,0));
			enemyGroup.add(new Enemy(new FlxPoint(350, 210), "size4", true,0));
			enemyGroup.add(new Enemy(new FlxPoint(224, 232), "size4", true,2));
		
			super.create();
		}
		public function damageEnemy(enemy:Enemy):void
		{
			if (enemy.health - 30 < 1)
				player1.points ++;
			enemy.hurt(30);
			FlxG.log("Health = " + enemy.health);
		}
		private function weaponShoot()
		{
			FlxG.log("X = " + FlxG.mouse.x + ", Y = " + FlxG.mouse.y);
			FlxG.play(gunfire);
			player1.ammo --;
			ammoUpdate();
			character.animShoot();
			shootGroup.add(new WeaponExplosion(character));
			
			var mapobjs :Array = mapGroup.members;
			var isProtected:Boolean = false;
			for (var i:int = 0; i < mapGroup.length; i++) {
				var mapobj :MapObj = mapobjs[i];
				
				if (mapobj != null && mapobj.alive && FlxCollision.pixelPerfectCheck(sight.center, mapobj))
				{
					isProtected = true;
					break;
				}
			}
			
			if (isProtected == false)
			{
				var enemies :Array = enemyGroup.members;
				for (var i:int = 0; i < enemies.length; i++) {
					var enemy :Enemy = enemies[i];
					
					if (enemy != null && enemy.alive && FlxCollision.pixelPerfectCheck(sight.center, enemy))
					{
						damageEnemy(enemy);
						break;
					}
				}
			}
			FlxG.log("    " + player1.points);
		}
		private function weaponReload()
		{
			FlxG.play(reload);
			player1.isReloading = 1;
			player1.ammo = player1.maxAmmo;
			ammoUpdate();
		}
		private function ammoUpdate()
		{
			var strAmmo = player1.ammo + "/" + player1.maxAmmo;
			ammoText.text = strAmmo;
			if (player1.ammo == 0)
				ammoText.color = 0xFFFF0000;
			else if(player1.ammo == 8)
				ammoText.color = 0xFFFFFFFF;
		}
		private function healthUpdate()
		{
			var strHealth = "" + player1.health;
			healthText.text = strHealth;
			if (player1.health < 20)
				healthText.color = 0xFFFF0000;
			else if(player1.health >= 20)
				healthText.color = 0xFFFFFFFF;
		}
		override public function update():void
		{
			//FlxG.log("X=" + FlxG.mouse.x + ", Y=" + FlxG.mouse.y);
			if (player1.isReloading)
			{
				player1.reloadingCounter += FlxG.elapsed;
				if (player1.reloadingCounter >= 0.4)
				{
					player1.reloadingCounter = 0.0;
					player1.isReloading = 0;
				}
			}
			if (FlxG.mouse.pressed())
			{
				if (!player1.isReloading)
				{
					if (player1.ammo > 0)
					{
						weaponShoot();
					}
				}
			}
			if (FlxG.keys.justPressed("R"))
			{
				if (!player1.isReloading)
				{
					if(player1.ammo != player1.maxAmmo)
						weaponReload();
				}
			}
			//RETIRAR DAQUI**********************
			if (FlxG.keys.justPressed("Z"))
			{
				player1.health --;
				healthUpdate();
			}
			if (FlxG.keys.justPressed("X"))
			{
				player1.health ++;
				healthUpdate();
			}
			//ATÉ AQUI***************************
			super.update();
		}
	}

}