// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (C) Jesse Taube <Mr.Bossman075@gmail.com>
 */

#include <clk-uclass.h>
#include <dm.h>
#include <clk/sunxi.h>
#include <dt-bindings/clock/suniv-ccu-f1c100s.h>
#include <dt-bindings/reset/suniv-ccu-f1c100s.h>
#include <linux/bitops.h>

static struct ccu_clk_gate suniv_gates[] = {
	[CLK_BUS_SPI0]	= GATE(0x60, BIT(20)), // refer to arch/arm/include/asm/arch-sunxi/clock_sun6i.h
};

static struct ccu_reset suniv_resets[] = {
	[RST_BUS_SPI0]	= RESET(0x2c0, BIT(20)),
};

static const struct ccu_desc suniv_ccu_desc = {
	.gates = suniv_gates,
	.resets = suniv_resets,
};

static int suniv_clk_bind(struct udevice *dev)
{
	return sunxi_reset_bind(dev, ARRAY_SIZE(suniv_resets));
}

static const struct udevice_id suniv_clk_ids[] = {
	{ .compatible = "allwinner,suniv-f1c100s-ccu",
	  .data = (ulong)&suniv_ccu_desc }
};

U_BOOT_DRIVER(clk_sun6i_suniv) = {
	.name		= "suniv_ccu",
	.id		= UCLASS_CLK,
	.of_match	= suniv_clk_ids,
	.priv_auto	= sizeof(struct ccu_priv),
	.ops		= &sunxi_clk_ops,
	.probe		= sunxi_clk_probe,
	.bind		= suniv_clk_bind,
};
