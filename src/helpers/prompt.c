/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:01:04 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/05 10:47:09 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// FONT: https://chrisyeh96.github.io/2020/03/28/terminal-colors.html
#define RED_PROMPT "\e[m\e[1;31m❯ \e[m"
#define GREEN_PROMPT "\e[m\e[1;32m❯ \e[m"

const char	*prompt(void)
{
	return ("Awesome text\n"GREEN_PROMPT);
}
