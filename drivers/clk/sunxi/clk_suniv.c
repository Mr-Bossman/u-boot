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
	[CLK_USB_PHY0]		=  { 0x0cc, BIT(1) },

	[CLK_BUS_DMA]		=  { 0x060, BIT(6) },
	[CLK_BUS_MMC0]		=  { 0x060, BIT(8) },
	[CLK_BUS_MMC1]		=  { 0x060, BIT(9) },
	[CLK_BUS_DRAM]		=  { 0x060, BIT(14) },
	[CLK_BUS_SPI0]		=  { 0x060, BIT(20) },
	[CLK_BUS_SPI1]		=  { 0x060, BIT(21) },
	[CLK_BUS_OTG]		=  { 0x060, BIT(24) },
	[CLK_BUS_VE]		=  { 0x064, BIT(0) },
	[CLK_BUS_LCD]		=  { 0x064, BIT(4) },
	[CLK_BUS_DEINTERLACE]	=  { 0x064, BIT(5) },
	[CLK_BUS_CSI]		=  { 0x064, BIT(8) },
	[CLK_BUS_TVD]		=  { 0x064, BIT(9) },
	[CLK_BUS_TVE]		=  { 0x064, BIT(10) },
	[CLK_BUS_DE_BE]		=  { 0x064, BIT(12) },
	[CLK_BUS_DE_FE]		=  { 0x064, BIT(14) },
	[CLK_BUS_CODEC]		=  { 0x068, BIT(0) },
	[CLK_BUS_SPDIF]		=  { 0x068, BIT(1) },
	[CLK_BUS_IR]		=  { 0x068, BIT(2) },
	[CLK_BUS_RSB]		=  { 0x068, BIT(3) },
	[CLK_BUS_I2S0]		=  { 0x068, BIT(12) },
	[CLK_BUS_I2C0]		=  { 0x068, BIT(16) },
	[CLK_BUS_I2C1]		=  { 0x068, BIT(17) },
	[CLK_BUS_I2C2]		=  { 0x068, BIT(18) },
	[CLK_BUS_UART0]		=  { 0x068, BIT(20) },
	[CLK_BUS_UART1]		=  { 0x068, BIT(21) },
	[CLK_BUS_UART2]		=  { 0x068, BIT(22) },
};

static struct ccu_reset suniv_resets[] = {
	[RST_USB_PHY0]		=  { 0x0cc, BIT(0) },

	[RST_BUS_DMA]		=  { 0x2c0, BIT(6) },
	[RST_BUS_MMC0]		=  { 0x2c0, BIT(8) },
	[RST_BUS_MMC1]		=  { 0x2c0, BIT(9) },
	[RST_BUS_DRAM]		=  { 0x2c0, BIT(14) },
	[RST_BUS_SPI0]		=  { 0x2c0, BIT(20) },
	[RST_BUS_SPI1]		=  { 0x2c0, BIT(21) },
	[RST_BUS_OTG]		=  { 0x2c0, BIT(24) },
	[RST_BUS_VE]		=  { 0x2c4, BIT(0) },
	[RST_BUS_LCD]		=  { 0x2c4, BIT(4) },
	[RST_BUS_DEINTERLACE]	=  { 0x2c4, BIT(5) },
	[RST_BUS_CSI]		=  { 0x2c4, BIT(8) },
	[RST_BUS_TVD]		=  { 0x2c4, BIT(9) },
	[RST_BUS_TVE]		=  { 0x2c4, BIT(10) },
	[RST_BUS_DE_BE]		=  { 0x2c4, BIT(12) },
	[RST_BUS_DE_FE]		=  { 0x2c4, BIT(14) },
	[RST_BUS_CODEC]		=  { 0x2d0, BIT(0) },
	[RST_BUS_SPDIF]		=  { 0x2d0, BIT(1) },
	[RST_BUS_IR]		=  { 0x2d0, BIT(2) },
	[RST_BUS_RSB]		=  { 0x2d0, BIT(3) },
	[RST_BUS_I2S0]		=  { 0x2d0, BIT(12) },
	[RST_BUS_I2C0]		=  { 0x2d0, BIT(16) },
	[RST_BUS_I2C1]		=  { 0x2d0, BIT(17) },
	[RST_BUS_I2C2]		=  { 0x2d0, BIT(18) },
	[RST_BUS_UART0]		=  { 0x2d0, BIT(20) },
	[RST_BUS_UART1]		=  { 0x2d0, BIT(21) },
	[RST_BUS_UART2]		=  { 0x2d0, BIT(22) },
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
