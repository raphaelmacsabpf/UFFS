package  
{
	import org.flixel.*;
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
		public var camera:FlxCamera;
		
		
		override public function create():void
		{
			world = new World();
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
			
			add(world);
			add(character);
			add(sight);
			add(hud);
			add(healthText);
			add(ammoText);
			
			super.create();
		}
		private function weaponShoot()
		{
			FlxG.play(gunfire);
			player1.ammo --;
			ammoUpdate();
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