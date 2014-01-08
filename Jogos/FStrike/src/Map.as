package  
{
	import mx.core.FlexSprite;
	import org.flixel.*;
	import org.flixel.plugin.photonstorm.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Map extends FlxState
	{
		[Embed(source = "assets/gunfire.mp3", mimeType = "audio/mpeg")] private var gunfire:Class;
		[Embed(source = "assets/reload.mp3", mimeType = "audio/mpeg")] private var reload:Class;
		
		[Embed(source = "assets/miniblood.png")] public var ASSET_BLOOD1:Class;
		public var world:FlxSprite;
		public var character:Character;
		public var sight:Sight;
		public var hud:HUD;
		public var healthText:FlxText;
		public var ammoText:FlxText;
		public static var player1:Player;
		public var hudGroup:FlxGroup;
		public var enemyGroup:FlxGroup;
		public var mapGroup:FlxGroup;
		public var worldGroup:FlxGroup;
		public var shootGroup:FlxGroup;
		public var bloodGroup:FlxGroup;
		public var pickupGroup:FlxGroup;
		public var MAX_ENEMIES:uint;
		public var aEmitter:FlxEmitter;
		private var lastHealth:Number;
		public var elapsedTime:Number;
		public var lastTimeEnemyAdded:uint;
		
		override public function create():void
		{
			this.lastHealth = 100;
			this.elapsedTime = 0.0;
			this.lastTimeEnemyAdded = 0;
			hudGroup = new FlxGroup();
			enemyGroup = new FlxGroup();
			mapGroup = new FlxGroup();
			worldGroup = new FlxGroup();
			shootGroup = new FlxGroup();
			bloodGroup = new FlxGroup();
			pickupGroup = new FlxGroup();
			
			
			character = new Character();
			sight = new Sight();
			hud = new HUD();
			player1 = new Player();
		
			for (var i:int = 0; i < 100; i++)
				bloodGroup.add(new BloodHud());
			
			
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
			
			
			
			add(worldGroup);
			add(enemyGroup);
			add(mapGroup);
			add(shootGroup);
			add(character);
			add(pickupGroup);
			add(bloodGroup);
			add(hudGroup);
		
			super.create();
		}
		public function damageEnemy(enemy:Enemy):void
		{
			enemy.hurt(30);
			aEmitter = new FlxEmitter();
			aEmitter.makeParticles(ASSET_BLOOD1, 16, 32, true, 0);
			aEmitter.setXSpeed(-200, 200);
			aEmitter.setYSpeed(-3,450);
			aEmitter.setRotation( -720, 720);
			aEmitter.gravity = 100;
			aEmitter.x = FlxG.mouse.x;
			aEmitter.y = FlxG.mouse.y;
			aEmitter.start(true, 0.2);
			add(aEmitter);
		}
		public function onHurt():void
		{
			var bloodHud:BloodHud;
			for (var i:int = 0; i < 4; i++)
			{
				bloodHud= bloodGroup.getFirstAvailable() as BloodHud;
				if (bloodHud != null)
				{
					bloodHud.alpha = 1;
					bloodHud.reset(FlxG.width * FlxG.random(),FlxG.height * FlxG.random());
				}
			}
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
			var pickupobjs :Array = pickupGroup.members;
			for (var i:int = 0; i < pickupGroup.length; i++) {
				var pick :Pickup = pickupobjs[i];
				
				if (pick != null && pick.alive && FlxCollision.pixelPerfectCheck(sight.center, pick))
				{
					isProtected = true;
					pick.usePickup();
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
			if (player1.health < this.lastHealth)
				onHurt();
			this.lastHealth = player1.health;
			if (player1.health < 0)
				FlxG.switchState(new Looser());
		}
		override public function update():void
		{
			healthUpdate();
			this.elapsedTime += FlxG.elapsed;
			if (player1.isReloading)
			{
				player1.reloadingCounter += FlxG.elapsed;
				if (player1.reloadingCounter >= 0.4)
				{
					player1.reloadingCounter = 0.0;
					player1.isReloading = 0;
				}
			}
			if (FlxG.mouse.justPressed())
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
			/*if (FlxG.keys.pressed("Z"))
			{
				player1.health --;
				healthUpdate();
			}
			if (FlxG.keys.pressed("X"))
			{
				player1.health ++;3
				healthUpdate();
			}
			if (FlxG.keys.justPressed("C"))
			{
				enemyGroup.add(new Enemy(new EnemySpawnPoint(new FlxPoint(300, 210), "size4",0)));
				enemyGroup.add(new Enemy(new EnemySpawnPoint(new FlxPoint(350, 210), "size4",0)));
				enemyGroup.add(new Enemy(new EnemySpawnPoint(new FlxPoint(224, 232), "size4", 2)));
			}*/
			//ATÉ AQUI***************************
			super.update();
		}
	}

}