#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe09a23a6, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x97823d2e, "cdev_init" },
	{ 0xd248ff00, "__register_chrdev" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xc5850110, "printk" },
	{ 0x27900d89, "cdev_add" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x82824194, "param_ops_uint" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "347AB674A80EE2282BC4890");
